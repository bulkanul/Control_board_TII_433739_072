#include "server.h"
#include "tools.h"
#include "netif.h"

extern ip4_addr_t     ipaddr;
extern QueueHandle_t link_queueHandle;
extern ETH_HandleTypeDef heth;
extern struct netif gnetif;
extern volatile uint8_t tcp_rx_overflow;

struct netconn *ms_server_inst   = NULL;
struct netconn *ms_remote_client = NULL;

void server_handler(QueueHandle_t* tcp_rx_data_queue,QueueHandle_t* indication_queue){

	char debug_buffer[200];
	
	err_t bind_err   = ERR_CONN;
	err_t accept_err = ERR_CONN;
	err_t listen_err = ERR_CONN;
	err_t recv_err   = ERR_CONN;
	
	struct netbuf* buf = NULL;

	uint8_t tmp;
	uint8_t discard_tcp_line = 0;
	uint32_t recv_ok_timeout_last_tick = 0;
//	char tmp_char;

/* Infinite loop */
	for(;;)
	{
		if(netif_is_up(&gnetif))
		{
			if(ms_server_inst == NULL)
			{
				ms_server_inst = netconn_new(NETCONN_TCP);
				if(ms_server_inst == NULL)
				{
					debug_mess("Unable to allocate TCP server connection\r\n");
					osDelay(100);
					continue;
				}
			}

			if(bind_err != ERR_OK)
			{
				bind_err = netconn_bind(ms_server_inst, NULL, SERVER_PORT);
				sprintf(debug_buffer,"Bind static IP Address: %u.%u.%u.%u\r\n", (uint8_t)((uint32_t)(ipaddr.addr)&0x000000ff),
																				(uint8_t)(((uint32_t)(ipaddr.addr)&0x0000ff00)>>8),
																				(uint8_t)(((uint32_t)(ipaddr.addr)&0x00ff0000)>>16),
																				(uint8_t)(((uint32_t)(ipaddr.addr)&0xff000000)>>24));
				debug_mess(debug_buffer);
				sprintf(debug_buffer,"Bind port: %i\r\n",SERVER_PORT);
				debug_mess(debug_buffer);
			}
			else
			{
				if(listen_err != ERR_OK)
				{
					listen_err = netconn_listen(ms_server_inst);
					sprintf(debug_buffer,"Whait for client connecting to: %i ...\r\n",SERVER_PORT);
				  debug_mess(debug_buffer);
				}
				else
				{
					if(accept_err != ERR_OK)
					{
						netconn_set_nonblocking(ms_server_inst,1);
						netconn_set_recvtimeout(ms_server_inst,200);

						accept_err = netconn_accept(ms_server_inst, &ms_remote_client);

						if(accept_err == ERR_OK)
						{
							discard_tcp_line = 0;
							set_console_mode(DISABLE);
							netconn_set_recvtimeout(ms_remote_client,200);
							sprintf(debug_buffer,"Connection established whith: %u.%u.%u.%u\r\n", (uint8_t)((uint32_t)(ms_remote_client->pcb.ip->remote_ip.addr)&0x000000ff),
																								  (uint8_t)(((uint32_t)(ms_remote_client->pcb.ip->remote_ip.addr)&0x0000ff00)>>8),
																								  (uint8_t)(((uint32_t)(ms_remote_client->pcb.ip->remote_ip.addr)&0x00ff0000)>>16),
																								  (uint8_t)(((uint32_t)(ms_remote_client->pcb.ip->remote_ip.addr)&0xff000000)>>24));
						  debug_mess(debug_buffer);
						  recv_ok_timeout_last_tick = osKernelSysTick();
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
									debug_mess("TCP receive buffer read failed\r\n");
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
										debug_mess("TCP receive queue full; dropping input until end of line\r\n");
									}
								}
							} while(netbuf_next(buf) >= 0);

							netbuf_delete(buf);
							buf = NULL;

							if(recv_err == ERR_OK)
							{
								tmp = ETH_IND_REQ;
								if(xQueueSend(*indication_queue,&tmp,0) != pdPASS)
									debug_mess("TCP indication queue is full\r\n");
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
								debug_mess("TCP receive returned no buffer\r\n");
								recv_err = ERR_CONN;
							}
							if(get_console_mode() == ENABLE)
							{
								if(osKernelSysTick() - recv_ok_timeout_last_tick > 3600000)
								{
									recv_err = ERR_CLSD;
								}
							}
							else
							{
								if(osKernelSysTick() - recv_ok_timeout_last_tick > RECV_OK_TIMEOUT)
								{
							//		recv_err = ERR_CLSD;
								}
							}
						}

						if(recv_err != ERR_OK && recv_err != ERR_TIMEOUT && recv_err != ERR_WOULDBLOCK)
						{
							debug_mess("Client disconnected\r\n");
							accept_err = recv_err;
							if(ms_remote_client != NULL)
							{
								netconn_close(ms_remote_client);
								netconn_delete(ms_remote_client);
								ms_remote_client = NULL;
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
			//	struct tcp_pcb* tcp = ms_remote_client->pcb.tcp;
				netconn_close(ms_remote_client);
				netconn_delete(ms_remote_client);
				ms_remote_client = NULL;
				discard_tcp_line = 0;
				//if(tcp)
				//	tcp_abort(tcp);
			}

			accept_err = ERR_CONN;
			recv_err   = ERR_CONN;
			osDelay(1);
		}
		osDelay(1);
	}

}

void ethernetif_notify_conn_changed(struct netif *netif){
	uint8_t link_state;
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	if(netif_is_link_up(netif)){
		link_state = 1;
		netif_set_up(netif);
	}
	else {
		link_state = 0;
		netif_set_down(netif);
	}
	xQueueSendFromISR(link_queueHandle,&link_state,&xHigherPriorityTaskWoken);
}


struct netconn* getRemoteClient(){
	return ms_remote_client;
}
