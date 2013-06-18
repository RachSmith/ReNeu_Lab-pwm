/*
 * FPGA Interface C API example for GCC for computers running Linux.
 *
 * NOTE: In order to run this example, you must compile a LabVIEW FPGA bitfile
 *       and generate a C API for it. For more information about using this
 *       example, refer to the Examples topic of the FPGA Interface C API Help,
 *       located under
 *       Start>>All Programs>>National Instruments>>FPGA Interface C API.
 */

#include "NiFpga_Math_Pid.h"
#include <stdio.h>
#include <stdlib.h>
#define TICKS_PER_DEGREE 1024/360  
 // ticks per revolution divided by 360 to get ticks per degree
#define ACCURACY 10000
 
double tick_degree(int32_t tick)
{
	double degree; 	
	degree = tick / TICKS_PER_DEGREE; 
	return degree; 
} 

int32_t degree_tick(double degree) 
{	
	int32_t tick; 
	tick = degree * TICKS_PER_DEGREE;
	return tick; 
}

int main()
{
	double desired_angle;
	int32_t desired_tick;
	int32_t Kd = .5 * ACCURACY;
	int32_t Kp = 5 * ACCURACY; 
	int32_t Ki = .0001 * ACCURACY;  
	int32_t error=0xFFFF; 
   /* must be called before any other calls */
   printf("Initializing...\n");
   NiFpga_Status status = NiFpga_Initialize();
   if (NiFpga_IsNotError(status))
   {
      NiFpga_Session session;
      /* opens a session, downloads the bitstream, and runs the FPGA */
      printf("Opening a session...\n");
      NiFpga_MergeStatus(&status, 
			NiFpga_Open(NiFpga_Math_Pid_Bitfile, NiFpga_Math_Pid_Signature,
                     "rio://146.6.84.251/RIO0",
                      NiFpga_OpenAttribute_NoRun,&session));
      if (NiFpga_IsNotError(status))
      {
         /* run the FPGA application */
         printf("Running the FPGA...\n");
         NiFpga_MergeStatus(&status, NiFpga_Run(session, 0));	
/********************************************************************/
			/* Code goes here */
			NiFpga_MergeStatus(&status,
							NiFpga_WriteBool(session,NiFpga_Encoder_Reset,0)); 
			NiFpga_MergeStatus(&status, 
							NiFpga_WriteI32(session,NiFpga_Kd,Kd));
			NiFpga_MergeStatus(&status, 
							NiFpga_WriteI32(session,NiFpga_Kp,Kp));
			NiFpga_MergeStatus(&status, 
							NiFpga_WriteI32(session,NiFpga_Ki,Ki));
			NiFpga_MergeStatus(&status, 
							NiFpga_WriteI32(session,NiFpga_Accuracy,ACCURACY));
			printf("Enter Desired(in degrees): ");
			scanf("%lf",&desired_angle); 
			desired_tick = degree_tick(desired_angle); 
			printf("Desired(in ticks) %d\n", desired_tick);  
			NiFpga_MergeStatus(&status, 
					NiFpga_WriteI32(session,NiFpga_Desired,desired_tick));
			printf("Entering loop\n"); 
			while(error != 0) {
				NiFpga_MergeStatus(&status, 
							NiFpga_ReadI32(session,NiFpga_RealError,&error));   				printf("Error:%d\n", error); 
			}	
/********************************************************************/
			/* Stopping */
			printf("Press <Enter> to stop and quit...");
         getchar(); 
         /* stop the FPGA loops */
         printf("Stopping the FPGA...\n");
	 		/* close the session now that we're done */
         printf("Closing the session...\n");
         NiFpga_MergeStatus(&status, NiFpga_Close(session, 0));
      }
      /* must be called after all other calls */
      printf("Finalizing...\n");
      NiFpga_MergeStatus(&status, NiFpga_Finalize());
   }
   /* check if anything went wrong */
   if (NiFpga_IsError(status))
   {
      printf("Error %d!\n", status);
      printf("Press <Enter> to quit...\n");
      getchar();
   }
   return status;
}
