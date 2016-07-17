#include "queue_handle_data.h"

float xiansu(float v)                        //防止速度过快
{
   if(v>2) 
     {
	    return 2;
	 }
   if(v<-2) 
     {
	    return -2;
	 } 
   else
   {
        return v;
   }

}
void handle_data(uint8_t buf[])
{		
		u8 byte1[4],byte2[4],byte3[4],byte4[4];
	
		byte1[0] = buf[0];
		byte1[1] = buf[1];
		byte1[2] = buf[2];
		byte1[3] = buf[3];	
    memcpy(&basketballbot.single_expected_speed.M1,byte1,sizeof(int));	  
		basketballbot.single_expected_speed.M1=xiansu(basketballbot.single_expected_speed.M1);
	
		byte2[0] = buf[4];
		byte2[1] = buf[5];
		byte2[2] = buf[6];
		byte2[3] = buf[7];	
    memcpy(&basketballbot.single_expected_speed.M2,byte2,sizeof(int));	  
		basketballbot.single_expected_speed.M2=xiansu(basketballbot.single_expected_speed.M2);
	
		byte3[0] = buf[8];
		byte3[1] = buf[9];
		byte3[2] = buf[10];
		byte3[3] = buf[11];	
    memcpy(&basketballbot.single_expected_speed.M3,byte3,sizeof(int));	 
		basketballbot.single_expected_speed.M3=xiansu(basketballbot.single_expected_speed.M3);
		
		byte4[0] = buf[12];
		byte4[1] = buf[13];
		byte4[2] = buf[14];
		byte4[3] = buf[15];	
    memcpy(&basketballbot.single_expected_speed.M4,byte4,sizeof(int));	  
		basketballbot.single_expected_speed.M4=xiansu(basketballbot.single_expected_speed.M4);
}
