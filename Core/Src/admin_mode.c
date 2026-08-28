#include "../Inc/admin_mode.h"
#include "../Inc/tools.h"
#include "math.h"

void admin_command(device_struct* mcs, char* resp, char* debug_buffer, char* tcp_buffer, int i)
{
	int err = 0, id;
	id = check_type_id(tcp_buffer, "admn", ADMN_COUNT);
	if (id != -1) {
		config_struct* conf = &mcs->config;

//-----------REQUEST SET CONF ----------------
		if (cmd("lgstatus admn")){
			response("lrstatus admn %i\r\n",
					id
					);
		}
		else if (cmd("lsconf admn")) {
			rd("lsconf admn %i %i %i %f %f %f %f %f %f %f %f %f %f %f %f %f %f\r\n",
				&id,
				&conf->therm_resi,
				&conf->therm_beta,
				&conf->v_ref,
				&conf->alarm_pd_lvl[0],
				&conf->alarm_pd_lvl[1],
				&conf->alarm_pd_lvl[2],
				&conf->alarm_pd_lvl[3],
				&conf->hpld1000_curr[0],
				&conf->hpld1000_curr[1],
				&conf->hpld1500_curr[0],
				&conf->hpld1500_curr[1],
				&conf->hpld1500_curr[2],
				&conf->hpld1500_curr[3],
				&conf->hpld1500_curr[4],
				&conf->hpld1500_curr[5],
				&conf->hpld1500_curr[6]
			);
			response("lrconf admn %i %i %i %f %f %f %f %f %f %f %f %f %f %f %f %f %f\r\n",
				id,
				conf->therm_resi,
				conf->therm_beta,
				conf->v_ref,
				conf->alarm_pd_lvl[0],
				conf->alarm_pd_lvl[1],
				conf->alarm_pd_lvl[2],
				conf->alarm_pd_lvl[3],
				conf->hpld1000_curr[0],
				conf->hpld1000_curr[1],
				conf->hpld1500_curr[0],
				conf->hpld1500_curr[1],
				conf->hpld1500_curr[2],
				conf->hpld1500_curr[3],
				conf->hpld1500_curr[4],
				conf->hpld1500_curr[5],
				conf->hpld1500_curr[6]
			);
		}
//-----------REQUEST GET CONF ----------------
		else if (cmd("lgconf admn")) {
			response("lrconf admn %i %i %i %f %f %f %f %f %f %f %f %f %f %f %f %f %f\r\n",
				id,
				conf->therm_resi,
				conf->therm_beta,
				conf->v_ref,
				conf->alarm_pd_lvl[0],
				conf->alarm_pd_lvl[1],
				conf->alarm_pd_lvl[2],
				conf->alarm_pd_lvl[3],
				conf->hpld1000_curr[0],
				conf->hpld1000_curr[1],
				conf->hpld1500_curr[0],
				conf->hpld1500_curr[1],
				conf->hpld1500_curr[2],
				conf->hpld1500_curr[3],
				conf->hpld1500_curr[4],
				conf->hpld1500_curr[5],
				conf->hpld1500_curr[6]
			);
		}
//-----------REQUEST SET SAVE CONF ------------
		else if(cmd("lssave admn")){
			err += save_last_config_data(conf, sizeof(config_struct));
			response("lrsave admn %i OK\r\n",id);
		}

		if (err != 0)
			err_cmd(resp, tcp_buffer, id);

	}
}
