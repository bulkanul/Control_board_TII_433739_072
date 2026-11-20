#include "server.h"
#include "tools.h"
#include "netif.h"
#include "lwip/tcpip.h"

extern QueueHandle_t link_queueHandle;
extern struct netif gnetif;
extern volatile uint8_t tcp_rx_overflow;

struct netconn *ms_server_inst   = NULL;
struct netconn *ms_remote_client = NULL;

static err_t delete_netconn(struct netconn **conn)
{
	err_t err;

	if(*conn == NULL)
		return ERR_OK;

	err = netconn_delete(*conn);
	if(err == ERR_OK)
		*conn = NULL;

	return err;
}

static void abort_netconn_tcp(struct netconn *conn)
{
	if(conn == NULL)
		return;

	LOCK_TCPIP_CORE();
	if(conn->pcb.tcp != NULL)
		tcp_abort(conn->pcb.tcp);
	UNLOCK_TCPIP_CORE();
}

void server_handler(QueueHandle_t* tcp_rx_data_queue,QueueHandle_t* indication_queue){

	err_t bind_err   = ERR_CONN;
	err_t accept_err = ERR_CONN;
	err_t listen_err = ERR_CONN;
	err_t recv_err   = ERR_CONN;
	
	struct netbuf* buf = NULL;

	uint8_t discard_tcp_line = 0;
	uint32_t recv_ok_timeout_last_tick = 0;

	for(;;)
	{
		if(netif_is_up(&gnetif) && netif_is_link_up(&gnetif))
		{
			if(ms_server_inst == NULL)
			{
				ms_server_inst = netconn_new(NETCONN_TCP);
				if(ms_server_inst == NULL) { osDelay(100); continue; }
			}

			if(bind_err != ERR_OK) { bind_err = netconn_bind(ms_server_inst, NULL, SERVER_PORT); }
			else
			{
				if(listen_err != ERR_OK) { listen_err = netconn_listen(ms_server_inst); }
				else
				{
					if(accept_err != ERR_OK)
					{
						if(ms_remote_client != NULL)
						{
							abort_netconn_tcp(ms_remote_client);
							if(delete_netconn(&ms_remote_client) != ERR_OK)
							{
								osDelay(1);
								continue;
							}
						}

						netconn_set_nonblocking(ms_server_inst,1);

						accept_err = netconn_accept(ms_server_inst, &ms_remote_client);

						if(accept_err == ERR_OK)
						{
							discard_tcp_line = 0;
							set_console_mode(DISABLE);
							netconn_set_recvtimeout(ms_remote_client,200);
							recv_ok_timeout_last_tick = osKernelSysTick();
						}
						else if(accept_err != ERR_WOULDBLOCK)
						{
							if(delete_netconn(&ms_server_inst) == ERR_OK)
							{
								bind_err = ERR_CONN;
								listen_err = ERR_CONN;
								accept_err = ERR_CONN;
							}
						}
					}
					else
					{
						set_interface_in(INTERFACE_ETHERNET);
						buf = NULL;
						recv_err = netconn_recv(ms_remote_client, &buf);
						if(recv_err == ERR_OK && buf != NULL)
						{
							do
							{
								void *payload;
								u16_t payload_len;
								err_t data_err = netbuf_data(buf, &payload, &payload_len);
								if(data_err != ERR_OK)
								{
									recv_err = ERR_CONN;
									break;
								}

								for(u16_t i = 0; i < payload_len; i++)
								{
									char received_char = ((char *)payload)[i];
									if(discard_tcp_line)
									{
										if(received_char == '\r' || received_char == '\n')
											discard_tcp_line = 0;
										continue;
									}

									if(xQueueSend(*tcp_rx_data_queue, (char *)payload + i, 0) != pdPASS)
									{
										tcp_rx_overflow = 1;
										xQueueReset(*tcp_rx_data_queue);
										discard_tcp_line = 1;
									}
								}
							} while(netbuf_next(buf) >= 0);

							netbuf_delete(buf);
							buf = NULL;

							if(recv_err == ERR_OK)
							{
								uint8_t tmp = ETH_IND_REQ;
								xQueueSend(*indication_queue,&tmp,0);
								recv_ok_timeout_last_tick = osKernelSysTick();
							}
						}
						else
						{
							if(buf != NULL)
							{
								netbuf_delete(buf);
								buf = NULL;
							}
							if(recv_err == ERR_OK)
							{
								recv_err = ERR_CONN;
							}
							if(get_console_mode() == ENABLE)
							{
								if(osKernelSysTick() - recv_ok_timeout_last_tick > 3600000)
								{
									recv_err = ERR_CLSD;
								}
							}
						}

						if(recv_err != ERR_OK && recv_err != ERR_TIMEOUT && recv_err != ERR_WOULDBLOCK)
						{
							accept_err = recv_err;
							if(ms_remote_client != NULL)
							{
								abort_netconn_tcp(ms_remote_client);
								delete_netconn(&ms_remote_client);
							}
							discard_tcp_line = 0;
						}
					}
				}
			}
		}
		else
		{
			if(ms_remote_client != NULL)
			{
				abort_netconn_tcp(ms_remote_client);
				delete_netconn(&ms_remote_client);
				discard_tcp_line = 0;
			}
			if(ms_server_inst != NULL)
				delete_netconn(&ms_server_inst);
			if(ms_server_inst == NULL)
			{
				bind_err = ERR_CONN;
				listen_err = ERR_CONN;
			}

			accept_err = ERR_CONN;
			recv_err   = ERR_CONN;
			osDelay(1);
		}
		osDelay(1);
	}

}

struct netconn* getRemoteClient(){
	return ms_remote_client;
}
