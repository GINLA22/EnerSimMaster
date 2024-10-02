
#include <stdio.h>
#include"types.h"
#include"WaterSourceStruct.h"
#include"WaterSinkStruct.h"
#include"InputData.h"
#include"WaterPipeStruct.h"
#include"WaterTwowayStruct.h"
#include"WaterTeeStruct.h"
#include"WaterCrossStruct.h"
#include"WaterPumpOLGStruct.h"
#include"WaterValveOnOffStruct.h"
#include"WaterOnewayStruct.h"
#include"WaterPRVStruct.h"
#include"Init.h"
#include"time.h"
#include"Calculate_v1.h"
int main()
{
	/// <summary>
 /// /Obtain data from the source and sink
 /// </summary>

/*printf("%s\n", GasSourceSinkFile);*/
	int linesSourceSink;
	int SourceDataCount = 0;
	int SinkDataCount = 0;
	int* PSourceDataCount = &SourceDataCount;
	int* PSinkDataCount = &SinkDataCount;
	WaterSourceStruct* SourceArray;// Here, the source and sink are written in the same struct, distinguished by MytType
	WaterSinkStruct* SinkArray;//Here, the source and sink are written in the same struct, distinguished by MytType
	linesSourceSink = GetRowNumFromFile(WaterSourceSinkFile);
	SourceArray = (WaterSourceStruct*)malloc(linesSourceSink * sizeof(WaterSourceStruct));
	SinkArray = (WaterSinkStruct*)malloc(linesSourceSink * sizeof(WaterSinkStruct));
	InPutGasSourceSinkDataProcess(SourceArray, SinkArray, PSourceDataCount, PSinkDataCount, WaterSourceSinkFile);
	printf("Successfully loaded source, total:% d; Successfully loaded remittance, total:%d个\n", SourceDataCount, SinkDataCount);

	//int i;
	//for (int i = 0; i < SourceDataCount;i++) {
	//	printf("%d\t%d\n",(SourceArray+i)->intNumber, (SourceArray + i)->intConnectedPipeNumber);
	//}
	//
	//for (int i = 0; i < SinkDataCount; i++) {
	//	printf("%d\t%d\n", (SinkArray+i)->intNumber, (SinkArray + i)->intConnectedPipeNumber);
	//}
	/// <summary>
	 /// /Obtain data from the source and sink
	 /// </summary>

	//******************************************************************//
		/// <summary>
	 /// /Retrieve data from Pipe
	 /// </summary>

	int linesPipe;
	int PipeDataCount = 0;
	int* PPipeDataCount = &PipeDataCount;
	WaterPipeStruct* PipeArray;// Here, the source and sink are written in the same struct, distinguished by MytType
	linesPipe = GetRowNumFromFile(WaterPipeFile);
	PipeArray = (WaterPipeStruct*)malloc(linesPipe * sizeof(WaterPipeStruct));
	InPutWaterPipeDataProcess(PipeArray, PPipeDataCount, WaterPipeFile);
	printf("Pipeline loading successful, total：%d个\n", PipeDataCount);
	//for (int i = 0; i < PipeDataCount; i++) {
	//	printf("%s\t%f\t%f\n", (PipeArray + i)->strName, (PipeArray + i)->dblLength, (PipeArray + i)->dblZ1);
	//}
	/// <summary>
	/// /Retrieve data from Pipe
	/// </summary>


	//******************************************************************//
	/// <summary>
	 /// /Obtain data from 2 channels
	 /// </summary>
	int linesTwoway;
	int TwowayDataCount = 0;
	int* PTwowayDataCount = &TwowayDataCount;
	WaterTwowayStruct* TwowayArray;// Here, the source and sink are written in the same struct, distinguished by MytType
	linesTwoway = GetRowNumFromFile(WaterTwowayFile);
	TwowayArray = (WaterTwowayStruct*)malloc(linesTwoway * sizeof(WaterTwowayStruct));
	InPutWaterTwowayDataProcess(TwowayArray, PTwowayDataCount, WaterTwowayFile);
	printf("Successfully loaded two-way communication, total：%d个\n", TwowayDataCount);
	//for (int i = 0; i < TwowayDataCount; i++) {
	//	printf("%s\t%d\t%d\n", (TwowayArray + i)->strName, (TwowayArray + i)->intNum, (TwowayArray + i)->Ports[1].ConnectPieceNo);
	//}
	/// <summary>
	/// /Obtain data from 2 channels
	/// </summary>

	//******************************************************************//

	/// <summary>
	/// /Obtain data from 3 channels
	/// </summary>
	int linesTee;
	int TeeDataCount = 0;
	int* PTeeDataCount = &TeeDataCount;
	WaterTeeStruct* TeeArray;// Here, the source and sink are written in the same struct, distinguished by MytType
	linesTee = GetRowNumFromFile(WaterTeeFile);
	TeeArray = (WaterTeeStruct*)malloc(linesTee * sizeof(WaterTeeStruct));
	InPutWaterTeeDataProcess(TeeArray, PTeeDataCount, WaterTeeFile);
	printf("Loading three-way successfully, total：%d个\n", TeeDataCount);
	//for (int i = 0; i < TeeDataCount; i++) {
	//	printf("%s\t%d\t%d\n", (TeeArray + i)->strName, (TeeArray + i)->intNum, (TeeArray + i)->Ports[1].ConnectPieceNo);
	//}
	/// <summary>
	/// /Obtain data from 3 channels
	/// </summary>
	//******************************************************************//



	 //******************************************************************//

	/// <summary>
	/// /Obtain data from 4 channels
	/// </summary>
	int linesCross;
	int CrossDataCount = 0;
	int* PCrossDataCount = &CrossDataCount;
	WaterCrossStruct* CrossArray;// Here, the source and sink are written in the same struct, distinguished by MytType
	linesCross = GetRowNumFromFile(WaterCrossFile);
	CrossArray = (WaterCrossStruct*)malloc(linesCross * sizeof(WaterCrossStruct));
	InPutWaterCrossDataProcess(CrossArray, PCrossDataCount, WaterCrossFile);
	printf("Loading four-way successfully, total:%d个\n", CrossDataCount);
	//for (int i = 0; i < CrossDataCount; i++) {
	//	printf("%s\t%d\t%d\n", (CrossArray + i)->strName, (CrossArray + i)->intNum, (CrossArray + i)->Ports[1].ConnectPieceNo);
	//}
	/// <summary>
	/// /Obtain data from 4 channels
	/// </summary>
	//******************************************************************//

	//******************************************************************//
	/// <summary>
	 /// /Obtain data from Block-1
	 /// </summary>
	int linesOneway;
	int OnewayDataCount = 0;
	int* POnewayDataCount = &OnewayDataCount;
	WaterOnewayStruct* OnewayArray;// Here, the source and sink are written in the same struct, distinguished by MytType
	linesOneway = GetRowNumFromFile(WaterOnewayFile);
	OnewayArray = (WaterOnewayStruct*)malloc(linesOneway * sizeof(WaterOnewayStruct));
	InPutWaterOnewayDataProcess(OnewayArray, POnewayDataCount, WaterOnewayFile);
	printf("Successfully loaded plugs, total：%d个\n", OnewayDataCount);
	//for (int i = 0; i < OnewayDataCount; i++) {
	//	printf("%s\t%d\t%d\n", (OnewayArray + i)->strName, (OnewayArray + i)->intNumber, (OnewayArray + i)->intConnectedPipeNumber);
	//}
	/// <summary>
	/// /Obtain data from Block-1
	/// </summary>

	//******************************************************************//

	//******************************************************************//

	/// <summary>
	/// /Obtain valve data
	/// </summary>
	int linesValveOnOff;
	int ValveOnOffDataCount = 0;
	int* PValveOnOffDataCount = &ValveOnOffDataCount;
	WaterValveOnOffStruct* ValveOnOffArray;// Here, the source and sink are written in the same struct, distinguished by MytType
	linesValveOnOff = GetRowNumFromFile(WaterValveOnOffFile);
	ValveOnOffArray = (WaterValveOnOffStruct*)malloc(linesValveOnOff * sizeof(WaterValveOnOffStruct));
	InPutWaterValveOnOffDataProcess(ValveOnOffArray, PValveOnOffDataCount, WaterValveOnOffFile);
	printf("Valve loading successful, total：%d个\n", ValveOnOffDataCount);
	//for (int i = 0; i < ValveOnOffDataCount; i++) {
	//	printf("%s\t%d\t%d\t%c\n", (ValveOnOffArray + i)->strName, (ValveOnOffArray + i)->intNum, (ValveOnOffArray + i)->Ports[1].ConnectPieceNo, (ValveOnOffArray + i)->blnOnOff);
	//}
	/// <summary>
	/// /Obtain valve data
	/// </summary>
	//******************************************************************//

	//******************************************************************//

	/// <summary>
	/// /Obtain data on the pressure reducing valve
	/// </summary>
	int linesPRV;
	int PRVDataCount = 0;
	int* PPRVDataCount = &PRVDataCount;
	WaterPRVStruct* PRVArray;// Here, the source and sink are written in the same struct, distinguished by MytType
	linesPRV = GetRowNumFromFile(WaterPRVFile);
	PRVArray = (WaterPRVStruct*)malloc(linesPRV * sizeof(WaterPRVStruct));
	InPutWaterPRVDataProcess(PRVArray, PPRVDataCount, WaterPRVFile);
	printf("Successfully loaded pressure reducing valve, total：%d个\n", PRVDataCount);
	//for (int i = 0; i < PRVDataCount; i++) {
	//	printf("%s\t%d\t%d\n", (PRVArray + i)->strName, (PRVArray + i)->intNum, (PRVArray + i)->Ports[1].ConnectPieceNo);
	//}
	/// <summary>
	////Obtain data on the pressure reducing valve
	/// </summary>
	//******************************************************************//

   //******************************************************************//

	/// <summary>
	/// /Obtain PumpOLG data
	/// </summary>
	int linesPumpOLG;
	int PumpOLGDataCount = 0;
	int* PPumpOLGDataCount = &PumpOLGDataCount;
	WaterPumpOLGStruct* PumpOLGArray;// Here, the source and sink are written in the same struct, distinguished by MytType
	linesPumpOLG = GetRowNumFromFile(WaterPumpOLGFile);
	PumpOLGArray = (WaterPumpOLGStruct*)malloc(linesPumpOLG * sizeof(WaterPumpOLGStruct));
	InPutWaterPumpOLGDataProcess(PumpOLGArray, PPumpOLGDataCount, WaterPumpOLGFile);
	printf("Loading booster pump group OLG successfully, total：%d个\n", PumpOLGDataCount);
	//for (int i = 0; i < PumpOLGDataCount; i++) {
	//	printf("%s\t%d\t%d\t%f\n", (PumpOLGArray + i)->strName, (PumpOLGArray + i)->intNum, (PumpOLGArray + i)->Ports[1].ConnectPieceNo, (PumpOLGArray + i)->dbla2);
	//}
	/// <summary>
	/// /Obtain PumpOLG data
	/// </summary>
	//******************************************************************//

	//******************************************************************//
	//******************************************************************//
	//******************************************************************//
	//******************************************************************//

	/// <summary>
	/// /Start initialization
	/// </summary>
	printf("Start initialization.......\n");
	DoWaterPipeDiscreticization(PipeArray, PipeDataCount);
	//for (int i = 0; i < PipeDataCount; i++) {
	//	printf("%s\t%f\t%f\n", (PipeArray + i)->strName, (PipeArray + i)->dblLength, (PipeArray + i)->dblVofSound);
	//}
	InitWaterPipe(PipeArray, PipeDataCount, Pinit, Tinit);
	//	for (int i = 0; i < PipeDataCount; i++) {
	//	printf("%s\t%f\t%f\t%f\n", (PipeArray + i)->strName, (PipeArray + i)->dblLength, (PipeArray + i)->dblZmid, (PipeArray + i)->dblKBmid);
	//}
	InitWaterSource(PipeArray, PipeDataCount, SourceArray, SourceDataCount);
	//for (int i = 0; i < SourceDataCount; i++) {
	//	printf("%s\t%f\t%d\n", (SourceArray + i)->strName, (SourceArray + i)->dblZ, (SourceArray + i)->clsPipe1->intNoPipe);
	//}
	InitWaterSink(PipeArray, PipeDataCount, SinkArray, SinkDataCount);
	//for (int i = 0; i < SinkDataCount; i++) {
	//	printf("%d\t%s\t%f\t%d\n", i,(SinkArray + i)->strName, (SinkArray + i)->dblZ, (SinkArray + i)->clsPipe1->intNoPipe);
	//}
	InitWaterTwoway(PipeArray, PipeDataCount, TwowayArray, TwowayDataCount);
	//for (int i = 0; i < TwowayDataCount; i++) {
	//	printf("%s\t%d\t%d\n", (TwowayArray + i)->strName, (TwowayArray + i)->clsPipe1->intNoPipe, (TwowayArray + i)->clsPipe2->intNoPipe);
	//}
	InitWaterTee(PipeArray, PipeDataCount, TeeArray, TeeDataCount);
	//for (int i = 0; i < TeeDataCount; i++) {
	//	printf("%s\t%d\t%d\t%d\n", (TeeArray + i)->strName, (TeeArray + i)->clsPipe1->intNoPipe, (TeeArray + i)->clsPipe2->intNoPipe,(TeeArray + i)->clsPipe3->intNoPipe);
	//}
	InitWaterCross(PipeArray, PipeDataCount, CrossArray, CrossDataCount);
	//for (int i = 0; i < CrossDataCount; i++) {
	//	printf("%s\t%d\t%d\t%d\n", (CrossArray + i)->strName, (CrossArray + i)->clsPipe1->intNoPipe, (CrossArray + i)->clsPipe2->intNoPipe, (CrossArray + i)->clsPipe3->intNoPipe);
	//}
	InitWaterOneway(PipeArray, PipeDataCount, OnewayArray, OnewayDataCount);
	//for (int i = 0; i < TwowayDataCount; i++) {
	//	printf("%s\t%d\n", (TwowayArray + i)->strName, (TwowayArray + i)->clsPipe1->intNoPipe);
	//}

	InitWaterValveOnOff(PipeArray, PipeDataCount, ValveOnOffArray, ValveOnOffDataCount);
	//for (int i = 0; i < ValveOnOffDataCount; i++) {
	//	printf("%s\t%d\n", (ValveOnOffArray + i)->strName, (ValveOnOffArray + i)->clsPipe1->intNoPipe);
	//}

	InitWaterPRV(PipeArray, PipeDataCount, PRVArray, PRVDataCount);
	//for (int i = 0; i < PRVDataCount; i++) {
	//	printf("%s\t%d\n", (PRVArray + i)->strName, (PRVArray + i)->clsPipe1->intNoPipe);
	//}


	InitWaterPumpOLG(PipeArray, PipeDataCount, PumpOLGArray, PumpOLGDataCount);
	//for (int i = 0; i < PumpOLGDataCount; i++) {
	//	printf("%s\t%d\n", (PumpOLGArray + i)->strName, (PumpOLGArray + i)->clsPipe1->intNoPipe);
	//}

	printf("End initialization.......\n");
	/// <summary>
	/// /End initialization
	/// </summar

	//******************************************************************//
	//******************************************************************//
	//******************************************************************//
	//******************************************************************//

	/// <summary>
	/// /Start calculating
	/// </summar
	clock_t start, start1, finish, finish1;
	double duration, duration1;
	start = clock();
	start1 = clock();
	printf("Start calculating.......\n");
	//******************************************************************//
	int indexCheck = 0;
	double TwowayErrP = 100000.0, TeeErrP = 100000.0, CrossErrP = 100000.0, ValveOnOffErrP = 100000.0, PRVErrP = 100000.0;
	for (int i = 0; i < TotalSimuTimeStep; i++) {

		//**************Calculate non pipe****************************************************//
		CalculateWaterSource(SourceArray, SourceDataCount);

		CalculateWaterSink(SinkArray, SinkDataCount);

		CalculateWaterTwoway(TwowayArray, TwowayDataCount);

		CalculateWaterTee(TeeArray, TeeDataCount);

		CalculateWaterCross(CrossArray, CrossDataCount);

		CalculateWaterOneway(OnewayArray, OnewayDataCount);

		CalculateWaterValveOnOff(ValveOnOffArray, ValveOnOffDataCount);

		CalculateWaterPRV(PRVArray, PRVDataCount);

		CalculateWaterPumpOLG(PumpOLGArray, PumpOLGDataCount);

		//printf("sink: %f,tee:%f,pipe:%f\n", (SinkArray + 213)->clsPipe1->dblKAmid, (TeeArray + 367)->clsPipe3->dblKAmid, (PipeArray + 21)->dblKAmid);
		//**************END Calculate non pipe****************************************************//


		//******************************************************************//
		//**************Calculate pipe****************************************************//
		CalculateWaterPipe(PipeArray, PipeDataCount);
		//**************END Calculate pipe****************************************************//
		//printf("pipeprocess:sink: %f,tee:%f,pipe:%f\n", (SinkArray + 213)->clsPipe1->dblKAmid, (TeeArray + 367)->clsPipe3->dblKAmid, (PipeArray + 21)->dblKAmid);
		indexCheck++;

		if (indexCheck % 1000 == 0) {
			//**************Refresh components****************************************************//
			RefreshWaterSource(SourceArray, SourceDataCount);
			RefreshWaterSink(SinkArray, SinkDataCount);
			RefreshWaterTwoway(TwowayArray, TwowayDataCount);
			RefreshWaterTee(TeeArray, TeeDataCount);
			RefreshWaterCross(CrossArray, CrossDataCount);
			RefreshWaterOneway(OnewayArray, OnewayDataCount);
			RefreshWaterValveOnOff(ValveOnOffArray, ValveOnOffDataCount);
			RefreshWaterPRV(PRVArray, PRVDataCount);
			RefreshWaterPumpOLG(PumpOLGArray, PumpOLGDataCount);

			RefreshWaterPipe(PipeArray, PipeDataCount);

			//**************END Refresh components****************************************************//





		}

		if (i % 10000 == 0) {
			//External loop, check the time consumption every 10000 times
			finish1 = clock();
			duration1 = (double)(finish1 - start1) / CLOCKS_PER_SEC;
			printf("Twoway-iter:%d\tTee-iter:%d\tCross-iter:%d\tPRV-iter:%d \t耗时：%f 秒......\n", i, i, i, i, duration1);
			start1 = finish1;
		}

	}
	//******************************************************************//
//**************The last refresh did not refresh all component tubes****************************************************//
	RefreshWaterSource(SourceArray, SourceDataCount);
	RefreshWaterSink(SinkArray, SinkDataCount);
	RefreshWaterTwoway(TwowayArray, TwowayDataCount);
	RefreshWaterTee(TeeArray, TeeDataCount);
	RefreshWaterCross(CrossArray, CrossDataCount);
	RefreshWaterOneway(OnewayArray, OnewayDataCount);
	RefreshWaterValveOnOff(ValveOnOffArray, ValveOnOffDataCount);
	RefreshWaterPRV(PRVArray, PRVDataCount);
	RefreshWaterPumpOLG(PumpOLGArray, PumpOLGDataCount);

	//**************End the last refresh of all components. The tubes were not refreshed****************************************************//

	printf("errPTwoway:%f\terrPTee:%f\terrPCross:%f\terrPPRV:%f\n", TwowayErrP, TeeErrP, CrossErrP, PRVErrP);

	//******************************************************************//
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("Calculation completed, total time consumed：%f 秒......\n", duration);
	/// <summary>
	/// /End calculation
	/// </summar

	//******************************************************************//
	//******************************************************************//
	//******************************************************************//
	//******************************************************************//


	//******************************************************************//
	//******************************************************************//
	//******************************************************************//
	//******************************************************************//

   /// <summary>
/// /This is the memory used to release the pointer variable requested above
/// </summary>
	//free(SourceArray);
	free(SourceArray);
	free(SinkArray);
	free(PipeArray);
	free(TwowayArray);
	free(TeeArray);
	free(CrossArray);
	free(OnewayArray);
	free(ValveOnOffArray);
	free(PRVArray);
	free(PumpOLGArray);
	/// <summary>
 /// /This is the memory used to release the pointer variable requested above
 /// </summary>

	return 0;
}

