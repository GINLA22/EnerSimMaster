#pragma once
#ifndef __WATERCROSS_STRUCT_H__
#define __WATERCROSS_STRUCT_H__
#include"WaterPipeStruct.h"


struct WaterCrossStruct {
	struct PipePort {
		double Dn;
		int ConnectPieceNo;
		int ConnectPortNo;
		double dblP;
		double dblU;
		double dblT;
		double dblM;
		double dblV;
	};

	char* strName;
	int intNum;
	int intType;
	PipePort Ports[5];
	WaterPipeStruct* clsPipe1;
	WaterPipeStruct* clsPipe2;
	WaterPipeStruct* clsPipe3;
	WaterPipeStruct* clsPipe4;
	double dblTmix;
	double dblErrP;
	char blnConnected;//y  or   c
	int TubeNum;
	int TubeType;


	void New1(WaterCrossStruct*) {

	}

	void New2(WaterCrossStruct* object, int intTheCrossNum, char* strTheCrossName, int intTheCrossConnPiece1,
		int intTheCrossConnPort1, int intTheCrossConnPiece2, int intTheCrossConnPort2,
		int intTheCrossConnPiece3, int intTheCrossConnPort3, int intTheCrossConnPiece4, int intTheCrossConnPort4) {

		object->intNum = intTheCrossNum;

		object->Ports[1].ConnectPieceNo = intTheCrossConnPiece1;
		object->Ports[1].ConnectPortNo = intTheCrossConnPort1;
		object->Ports[1].Dn = 1.0;
		object->Ports[2].ConnectPieceNo = intTheCrossConnPiece2;
		object->Ports[2].ConnectPortNo = intTheCrossConnPort2;
		object->Ports[2].Dn = 1.0;
		object->Ports[3].ConnectPieceNo = intTheCrossConnPiece3;
		object->Ports[3].ConnectPortNo = intTheCrossConnPort3;
		object->Ports[3].Dn = 1.0;
		object->Ports[4].ConnectPieceNo = intTheCrossConnPiece4;
		object->Ports[4].ConnectPortNo = intTheCrossConnPort4;
		object->Ports[4].Dn = 1.0;
		object->TubeNum = intTheCrossNum;
		object->TubeType = WaterCross;




	}

	void Init(WaterCrossStruct* obj, WaterPipeStruct* pipe1, WaterPipeStruct* pipe2, WaterPipeStruct* pipe3, WaterPipeStruct* pipe4) {
		obj->clsPipe1 = pipe1;
		obj->clsPipe2 = pipe2;
		obj->clsPipe3 = pipe3;
		obj->clsPipe4 = pipe4;
		obj->CheckCrossType(obj);
		obj->Ports[1].Dn = pipe1->dblDiameter;
		obj->Ports[2].Dn = pipe2->dblDiameter;
		obj->Ports[3].Dn = pipe3->dblDiameter;
		obj->Ports[4].Dn = pipe4->dblDiameter;


		switch (obj->intType) {
		case 1:
			obj->Ports[1].dblP = pipe1->Ports[2].dblP;
			obj->Ports[1].dblU = pipe1->Ports[2].dblU;
			obj->Ports[1].dblT = pipe1->Ports[2].dblT;
			obj->Ports[2].dblP = pipe2->Ports[2].dblP;
			obj->Ports[2].dblU = pipe2->Ports[2].dblU;
			obj->Ports[2].dblT = pipe2->Ports[2].dblT;
			obj->Ports[3].dblP = pipe3->Ports[2].dblP;
			obj->Ports[3].dblU = pipe3->Ports[2].dblU;
			obj->Ports[3].dblT = pipe3->Ports[2].dblT;
			obj->Ports[4].dblP = pipe4->Ports[1].dblP;
			obj->Ports[4].dblU = pipe4->Ports[1].dblU;
			obj->Ports[4].dblT = pipe4->Ports[1].dblT;
			break;
		case 2:
			obj->Ports[1].dblP = pipe1->Ports[2].dblP;
			obj->Ports[1].dblU = pipe1->Ports[2].dblU;
			obj->Ports[1].dblT = pipe1->Ports[2].dblT;
			obj->Ports[2].dblP = pipe2->Ports[2].dblP;
			obj->Ports[2].dblU = pipe2->Ports[2].dblU;
			obj->Ports[2].dblT = pipe2->Ports[2].dblT;
			obj->Ports[3].dblP = pipe3->Ports[1].dblP;
			obj->Ports[3].dblU = pipe3->Ports[1].dblU;
			obj->Ports[3].dblT = pipe3->Ports[1].dblT;
			obj->Ports[4].dblP = pipe4->Ports[2].dblP;
			obj->Ports[4].dblU = pipe4->Ports[2].dblU;
			obj->Ports[4].dblT = pipe4->Ports[2].dblT;
			break;
		case 3:
			obj->Ports[1].dblP = pipe1->Ports[2].dblP;
			obj->Ports[1].dblU = pipe1->Ports[2].dblU;
			obj->Ports[1].dblT = pipe1->Ports[2].dblT;
			obj->Ports[2].dblP = pipe2->Ports[2].dblP;
			obj->Ports[2].dblU = pipe2->Ports[2].dblU;
			obj->Ports[2].dblT = pipe2->Ports[2].dblT;
			obj->Ports[3].dblP = pipe3->Ports[1].dblP;
			obj->Ports[3].dblU = pipe3->Ports[1].dblU;
			obj->Ports[3].dblT = pipe3->Ports[1].dblT;
			obj->Ports[4].dblP = pipe4->Ports[1].dblP;
			obj->Ports[4].dblU = pipe4->Ports[1].dblU;
			obj->Ports[4].dblT = pipe4->Ports[1].dblT;
			break;
		case 4:
			obj->Ports[1].dblP = pipe1->Ports[2].dblP;
			obj->Ports[1].dblU = pipe1->Ports[2].dblU;
			obj->Ports[1].dblT = pipe1->Ports[2].dblT;
			obj->Ports[2].dblP = pipe2->Ports[1].dblP;
			obj->Ports[2].dblU = pipe2->Ports[1].dblU;
			obj->Ports[2].dblT = pipe2->Ports[1].dblT;
			obj->Ports[3].dblP = pipe3->Ports[2].dblP;
			obj->Ports[3].dblU = pipe3->Ports[2].dblU;
			obj->Ports[3].dblT = pipe3->Ports[2].dblT;
			obj->Ports[4].dblP = pipe4->Ports[2].dblP;
			obj->Ports[4].dblU = pipe4->Ports[2].dblU;
			obj->Ports[4].dblT = pipe4->Ports[2].dblT;
			break;
		case 5:
			obj->Ports[1].dblP = pipe1->Ports[2].dblP;
			obj->Ports[1].dblU = pipe1->Ports[2].dblU;
			obj->Ports[1].dblT = pipe1->Ports[2].dblT;
			obj->Ports[2].dblP = pipe2->Ports[1].dblP;
			obj->Ports[2].dblU = pipe2->Ports[1].dblU;
			obj->Ports[2].dblT = pipe2->Ports[1].dblT;
			obj->Ports[3].dblP = pipe3->Ports[2].dblP;
			obj->Ports[3].dblU = pipe3->Ports[2].dblU;
			obj->Ports[3].dblT = pipe3->Ports[2].dblT;
			obj->Ports[4].dblP = pipe4->Ports[1].dblP;
			obj->Ports[4].dblU = pipe4->Ports[1].dblU;
			obj->Ports[4].dblT = pipe4->Ports[1].dblT;
			break;
		case 6:
			obj->Ports[1].dblP = pipe1->Ports[2].dblP;
			obj->Ports[1].dblU = pipe1->Ports[2].dblU;
			obj->Ports[1].dblT = pipe1->Ports[2].dblT;
			obj->Ports[2].dblP = pipe2->Ports[1].dblP;
			obj->Ports[2].dblU = pipe2->Ports[1].dblU;
			obj->Ports[2].dblT = pipe2->Ports[1].dblT;
			obj->Ports[3].dblP = pipe3->Ports[1].dblP;
			obj->Ports[3].dblU = pipe3->Ports[1].dblU;
			obj->Ports[3].dblT = pipe3->Ports[1].dblT;
			obj->Ports[4].dblP = pipe4->Ports[2].dblP;
			obj->Ports[4].dblU = pipe4->Ports[2].dblU;
			obj->Ports[4].dblT = pipe4->Ports[2].dblT;
			break;
		case 7:
			obj->Ports[1].dblP = pipe1->Ports[2].dblP;
			obj->Ports[1].dblU = pipe1->Ports[2].dblU;
			obj->Ports[1].dblT = pipe1->Ports[2].dblT;
			obj->Ports[2].dblP = pipe2->Ports[1].dblP;
			obj->Ports[2].dblU = pipe2->Ports[1].dblU;
			obj->Ports[2].dblT = pipe2->Ports[1].dblT;
			obj->Ports[3].dblP = pipe3->Ports[1].dblP;
			obj->Ports[3].dblU = pipe3->Ports[1].dblU;
			obj->Ports[3].dblT = pipe3->Ports[1].dblT;
			obj->Ports[4].dblP = pipe4->Ports[1].dblP;
			obj->Ports[4].dblU = pipe4->Ports[1].dblU;
			obj->Ports[4].dblT = pipe4->Ports[1].dblT;
			break;
		case 8:
			obj->Ports[1].dblP = pipe1->Ports[1].dblP;
			obj->Ports[1].dblU = pipe1->Ports[1].dblU;
			obj->Ports[1].dblT = pipe1->Ports[1].dblT;
			obj->Ports[2].dblP = pipe2->Ports[2].dblP;
			obj->Ports[2].dblU = pipe2->Ports[2].dblU;
			obj->Ports[2].dblT = pipe2->Ports[2].dblT;
			obj->Ports[3].dblP = pipe3->Ports[2].dblP;
			obj->Ports[3].dblU = pipe3->Ports[2].dblU;
			obj->Ports[3].dblT = pipe3->Ports[2].dblT;
			obj->Ports[4].dblP = pipe4->Ports[2].dblP;
			obj->Ports[4].dblU = pipe4->Ports[2].dblU;
			obj->Ports[4].dblT = pipe4->Ports[2].dblT;
			break;
		case 9:
			obj->Ports[1].dblP = pipe1->Ports[1].dblP;
			obj->Ports[1].dblU = pipe1->Ports[1].dblU;
			obj->Ports[1].dblT = pipe1->Ports[1].dblT;
			obj->Ports[2].dblP = pipe2->Ports[2].dblP;
			obj->Ports[2].dblU = pipe2->Ports[2].dblU;
			obj->Ports[2].dblT = pipe2->Ports[2].dblT;
			obj->Ports[3].dblP = pipe3->Ports[2].dblP;
			obj->Ports[3].dblU = pipe3->Ports[2].dblU;
			obj->Ports[3].dblT = pipe3->Ports[2].dblT;
			obj->Ports[4].dblP = pipe4->Ports[1].dblP;
			obj->Ports[4].dblU = pipe4->Ports[1].dblU;
			obj->Ports[4].dblT = pipe4->Ports[1].dblT;
			break;
		case 10:
			obj->Ports[1].dblP = pipe1->Ports[1].dblP;
			obj->Ports[1].dblU = pipe1->Ports[1].dblU;
			obj->Ports[1].dblT = pipe1->Ports[1].dblT;
			obj->Ports[2].dblP = pipe2->Ports[2].dblP;
			obj->Ports[2].dblU = pipe2->Ports[2].dblU;
			obj->Ports[2].dblT = pipe2->Ports[2].dblT;
			obj->Ports[3].dblP = pipe3->Ports[1].dblP;
			obj->Ports[3].dblU = pipe3->Ports[1].dblU;
			obj->Ports[3].dblT = pipe3->Ports[1].dblT;
			obj->Ports[4].dblP = pipe4->Ports[2].dblP;
			obj->Ports[4].dblU = pipe4->Ports[2].dblU;
			obj->Ports[4].dblT = pipe4->Ports[2].dblT;
			break;
		case 11:
			obj->Ports[1].dblP = pipe1->Ports[1].dblP;
			obj->Ports[1].dblU = pipe1->Ports[1].dblU;
			obj->Ports[1].dblT = pipe1->Ports[1].dblT;
			obj->Ports[2].dblP = pipe2->Ports[2].dblP;
			obj->Ports[2].dblU = pipe2->Ports[2].dblU;
			obj->Ports[2].dblT = pipe2->Ports[2].dblT;
			obj->Ports[3].dblP = pipe3->Ports[1].dblP;
			obj->Ports[3].dblU = pipe3->Ports[1].dblU;
			obj->Ports[3].dblT = pipe3->Ports[1].dblT;
			obj->Ports[4].dblP = pipe4->Ports[1].dblP;
			obj->Ports[4].dblU = pipe4->Ports[1].dblU;
			obj->Ports[4].dblT = pipe4->Ports[1].dblT;
			break;
		case 12:
			obj->Ports[1].dblP = pipe1->Ports[1].dblP;
			obj->Ports[1].dblU = pipe1->Ports[1].dblU;
			obj->Ports[1].dblT = pipe1->Ports[1].dblT;
			obj->Ports[2].dblP = pipe2->Ports[1].dblP;
			obj->Ports[2].dblU = pipe2->Ports[1].dblU;
			obj->Ports[2].dblT = pipe2->Ports[1].dblT;
			obj->Ports[3].dblP = pipe3->Ports[2].dblP;
			obj->Ports[3].dblU = pipe3->Ports[2].dblU;
			obj->Ports[3].dblT = pipe3->Ports[2].dblT;
			obj->Ports[4].dblP = pipe4->Ports[2].dblP;
			obj->Ports[4].dblU = pipe4->Ports[2].dblU;
			obj->Ports[4].dblT = pipe4->Ports[2].dblT;
			break;
		case 13:
			obj->Ports[1].dblP = pipe1->Ports[1].dblP;
			obj->Ports[1].dblU = pipe1->Ports[1].dblU;
			obj->Ports[1].dblT = pipe1->Ports[1].dblT;
			obj->Ports[2].dblP = pipe2->Ports[1].dblP;
			obj->Ports[2].dblU = pipe2->Ports[1].dblU;
			obj->Ports[2].dblT = pipe2->Ports[1].dblT;
			obj->Ports[3].dblP = pipe3->Ports[2].dblP;
			obj->Ports[3].dblU = pipe3->Ports[2].dblU;
			obj->Ports[3].dblT = pipe3->Ports[2].dblT;
			obj->Ports[4].dblP = pipe4->Ports[1].dblP;
			obj->Ports[4].dblU = pipe4->Ports[1].dblU;
			obj->Ports[4].dblT = pipe4->Ports[1].dblT;
			break;
		case 14:
			obj->Ports[1].dblP = pipe1->Ports[1].dblP;
			obj->Ports[1].dblU = pipe1->Ports[1].dblU;
			obj->Ports[1].dblT = pipe1->Ports[1].dblT;
			obj->Ports[2].dblP = pipe2->Ports[1].dblP;
			obj->Ports[2].dblU = pipe2->Ports[1].dblU;
			obj->Ports[2].dblT = pipe2->Ports[1].dblT;
			obj->Ports[3].dblP = pipe3->Ports[1].dblP;
			obj->Ports[3].dblU = pipe3->Ports[1].dblU;
			obj->Ports[3].dblT = pipe3->Ports[1].dblT;
			obj->Ports[4].dblP = pipe4->Ports[2].dblP;
			obj->Ports[4].dblU = pipe4->Ports[2].dblU;
			obj->Ports[4].dblT = pipe4->Ports[2].dblT;
			break;
		}


	}

	void CheckCrossType(WaterCrossStruct* obj) {
		if (obj->Ports[1].ConnectPortNo == 2 && obj->Ports[2].ConnectPortNo == 1
			&& obj->Ports[3].ConnectPortNo == 2 && obj->Ports[4].ConnectPortNo == 1) {
			obj->intType = 3;
		}
		else if (obj->Ports[1].ConnectPortNo == 1 && obj->Ports[2].ConnectPortNo == 2
			&& obj->Ports[3].ConnectPortNo == 1 && obj->Ports[4].ConnectPortNo == 2) {
			obj->intType = 4;
		}
		else if (obj->Ports[1].ConnectPortNo == 2 && obj->Ports[2].ConnectPortNo == 2
			&& obj->Ports[3].ConnectPortNo == 1 && obj->Ports[4].ConnectPortNo == 1) {
			obj->intType = 5;
		}
		else if (obj->Ports[1].ConnectPortNo == 2 && obj->Ports[2].ConnectPortNo == 2
			&& obj->Ports[3].ConnectPortNo == 2 && obj->Ports[4].ConnectPortNo == 2) {
			obj->intType = 6;
		}
		else if (obj->Ports[1].ConnectPortNo == 2 && obj->Ports[2].ConnectPortNo == 2
			&& obj->Ports[3].ConnectPortNo == 2 && obj->Ports[4].ConnectPortNo == 1) {
			obj->intType = 1;
		}
		else if (obj->Ports[1].ConnectPortNo == 2 && obj->Ports[2].ConnectPortNo == 1
			&& obj->Ports[3].ConnectPortNo == 1 && obj->Ports[4].ConnectPortNo == 2) {
			obj->intType = 2;
		}
		else if (obj->Ports[1].ConnectPortNo == 2 && obj->Ports[2].ConnectPortNo == 1
			&& obj->Ports[3].ConnectPortNo == 1 && obj->Ports[4].ConnectPortNo == 1) {
			obj->intType = 16;
		}
		else if (obj->Ports[1].ConnectPortNo == 1 && obj->Ports[2].ConnectPortNo == 2
			&& obj->Ports[3].ConnectPortNo == 2 && obj->Ports[4].ConnectPortNo == 2) {
			obj->intType = 15;
		}
		else if (obj->Ports[1].ConnectPortNo == 1 && obj->Ports[2].ConnectPortNo == 2
			&& obj->Ports[3].ConnectPortNo == 2 && obj->Ports[4].ConnectPortNo == 1) {
			obj->intType = 14;
		}
		else if (obj->Ports[1].ConnectPortNo == 2 && obj->Ports[2].ConnectPortNo == 2
			&& obj->Ports[3].ConnectPortNo == 1 && obj->Ports[4].ConnectPortNo == 2) {
			obj->intType = 13;
		}
		else if (obj->Ports[1].ConnectPortNo == 1 && obj->Ports[2].ConnectPortNo == 2
			&& obj->Ports[3].ConnectPortNo == 1 && obj->Ports[4].ConnectPortNo == 1) {
			obj->intType = 12;
		}
		else if (obj->Ports[1].ConnectPortNo == 1 && obj->Ports[2].ConnectPortNo == 1
			&& obj->Ports[3].ConnectPortNo == 2 && obj->Ports[4].ConnectPortNo == 2) {
			obj->intType = 11;
		}
		else if (obj->Ports[1].ConnectPortNo == 1 && obj->Ports[2].ConnectPortNo == 1
			&& obj->Ports[3].ConnectPortNo == 1 && obj->Ports[4].ConnectPortNo == 1) {
			obj->intType = 10;
		}
		else if (obj->Ports[1].ConnectPortNo == 1 && obj->Ports[2].ConnectPortNo == 1
			&& obj->Ports[3].ConnectPortNo == 1 && obj->Ports[4].ConnectPortNo == 2) {
			obj->intType = 9;
		}
		else if (obj->Ports[1].ConnectPortNo == 2 && obj->Ports[2].ConnectPortNo == 1
			&& obj->Ports[3].ConnectPortNo == 2 && obj->Ports[4].ConnectPortNo == 2) {
			obj->intType = 9;
		}
		else if (obj->Ports[1].ConnectPortNo == 1 && obj->Ports[2].ConnectPortNo == 1
			&& obj->Ports[3].ConnectPortNo == 2 && obj->Ports[4].ConnectPortNo == 1) {
			obj->intType = 7;
		}
	}

	void DoHydraulic(WaterCrossStruct* obj) {
		double KA1;
		double KA2;
		double KA3;
		double KA4;
		double KB1;
		double KB2;
		double KB3;
		double KB4;
		double MyCurP;
		MyCurP = (obj->Ports[1].dblP + obj->Ports[2].dblP + obj->Ports[3].dblP + obj->Ports[4].dblP) / 4.0;
		switch (obj->intType) {
		case 1:
			KA1 = obj->clsPipe2->dblKAmid;
			KA2 = obj->clsPipe1->dblKAmid;
			KA3 = obj->clsPipe4->dblKAmid;
			KA4 = obj->clsPipe3->dblKAmid;
			KB1 = obj->CrossType1KB1(KA1, KA2, KA3, KA4, obj->clsPipe1->Area(obj->clsPipe2), obj->clsPipe1->dblRoughAve, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->dblRoughAve, obj->clsPipe3->Area(obj->clsPipe4), obj->clsPipe3->dblRoughAve, obj->clsPipe4->Area(obj->clsPipe1), obj->clsPipe4->dblRoughAve);
			KB2 = 1.0 * sqrt(KA1 + KA2) - KA2;
			KB3 = 1.0 * sqrt(KA1 + KB2) - KA3;
			KB4 = 1.0 * sqrt(KA1 + KB3) - KA4;


			obj->clsPipe1->dblPort2VKB = sqrt(KB1);
			obj->clsPipe2->dblPort2VKB = sqrt(KB2);
			obj->clsPipe3->dblPort2VKB = sqrt(KB3);
			obj->clsPipe4->dblPort2VKB = sqrt(KB4);

			break;
		case 2:
			KB1 = obj->clsPipe2->dblKBmid;
			KA2 = obj->clsPipe1->dblKAmid;
			KB3 = obj->clsPipe4->dblKBmid;
			KB4 = obj->clsPipe3->dblKBmid;
			KA1 = obj->CrossType2KB1(KB1, KA2, KB3, KB4, obj->clsPipe1->Area(obj->clsPipe2), obj->clsPipe1->dblRoughAve, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->dblRoughAve, obj->clsPipe3->Area(obj->clsPipe4), obj->clsPipe3->dblRoughAve, obj->clsPipe4->Area(obj->clsPipe1), obj->clsPipe4->dblRoughAve);

			KB2 = 1.0 * sqrt(KA1 + KB1) - KA2;
			KA3 = 1.0 * sqrt(KA1 + KB1) - KB3;
			KA4 = 1.0 * sqrt(KA1 + KB1) - KB4;

			obj->clsPipe1->dblPort1VKA = sqrt(KA1);
			obj->clsPipe2->dblPort2VKB = sqrt(KB2);
			obj->clsPipe3->dblPort1VKA = sqrt(KA3);
			obj->clsPipe4->dblPort1VKA = sqrt(KA4);

			break;
		case 3:
			KA1 = obj->clsPipe2->dblKAmid;
			KA2 = obj->clsPipe1->dblKAmid;
			KB3 = obj->clsPipe4->dblKBmid;
			KB4 = obj->clsPipe3->dblKBmid;
			KB1 = obj->CrossType3KB1(KA1, KA2, KB3, KB4, obj->clsPipe1->Area(obj->clsPipe2), obj->clsPipe1->dblRoughAve, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->dblRoughAve, obj->clsPipe3->Area(obj->clsPipe4), obj->clsPipe3->dblRoughAve, obj->clsPipe4->Area(obj->clsPipe1), obj->clsPipe4->dblRoughAve);
			KB2 = 1.0 * sqrt(KA1 + KB1) - KA2;
			KA3 = 1.0 * sqrt(KA1 + KB1) - KB3;
			KA4 = 1.0 * sqrt(KA1 + KB1) - KB4;
			obj->clsPipe1->dblPort2VKB = sqrt(KB1);
			obj->clsPipe2->dblPort2VKB = sqrt(KB2);
			obj->clsPipe3->dblPort1VKA = sqrt(KA3);
			obj->clsPipe4->dblPort1VKA = sqrt(KA4);

			break;

		case 4:
			KA1 = obj->clsPipe2->dblKAmid;
			KB2 = obj->clsPipe1->dblKBmid;
			KB3 = obj->clsPipe4->dblKBmid;
			KA4 = obj->clsPipe3->dblKAmid;
			KB1 = obj->CrossType4KB1(KA1, KB2, KB3, KA4, obj->clsPipe1->Area(obj->clsPipe2), obj->clsPipe1->dblRoughAve, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->dblRoughAve, obj->clsPipe3->Area(obj->clsPipe4), obj->clsPipe3->dblRoughAve, obj->clsPipe4->Area(obj->clsPipe1), obj->clsPipe4->dblRoughAve);

			KA2 = 1.0 * sqrt(KA1 + KB1) - KB2;
			KA3 = 1.0 * sqrt(KA1 + KB1) - KB3;
			KB4 = 1.0 * sqrt(KA1 + KB1) - KA4;
			obj->clsPipe1->dblPort2VKB = sqrt(KB1);
			obj->clsPipe2->dblPort1VKA = sqrt(KA2);
			obj->clsPipe3->dblPort1VKA = sqrt(KA3);
			obj->clsPipe4->dblPort2VKB = sqrt(KB4);

			break;

		case 5:
			KA1 = obj->clsPipe2->dblKAmid;
			KB2 = obj->clsPipe1->dblKBmid;
			KA3 = obj->clsPipe4->dblKAmid;
			KB4 = obj->clsPipe3->dblKBmid;
			KB1 = obj->CrossType5KB1(KA1, KB2, KA3, KB4, obj->clsPipe1->Area(obj->clsPipe2), obj->clsPipe1->dblRoughAve, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->dblRoughAve, obj->clsPipe3->Area(obj->clsPipe4), obj->clsPipe3->dblRoughAve, obj->clsPipe4->Area(obj->clsPipe1), obj->clsPipe4->dblRoughAve);

			KA2 = 1.0 * sqrt(KA1 + KB1) - KB2;
			KB3 = 1.0 * sqrt(KA1 + KB1) - KA3;
			KA4 = 1.0 * sqrt(KA1 + KB1) - KB4;
			obj->clsPipe1->dblPort2VKB = sqrt(KB1);
			obj->clsPipe2->dblPort1VKA = sqrt(KA2);
			obj->clsPipe3->dblPort2VKB = sqrt(KB3);
			obj->clsPipe4->dblPort1VKA = sqrt(KA4);

			break;

		case 6:
			KA1 = obj->clsPipe2->dblKAmid;
			KB2 = obj->clsPipe1->dblKBmid;
			KA3 = obj->clsPipe4->dblKAmid;
			KA4 = obj->clsPipe3->dblKBmid;
			KB1 = obj->CrossType6KB1(KA1, KB2, KA3, KA4, obj->clsPipe1->Area(obj->clsPipe2), obj->clsPipe1->dblRoughAve, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->dblRoughAve, obj->clsPipe3->Area(obj->clsPipe4), obj->clsPipe3->dblRoughAve, obj->clsPipe4->Area(obj->clsPipe1), obj->clsPipe4->dblRoughAve);

			KA2 = 1.0 * sqrt(KA1 + KB1) - KB2;
			KB3 = 1.0 * sqrt(KA1 + KB1) - KA3;
			KB4 = 1.0 * sqrt(KA1 + KB1) - KA4;
			obj->clsPipe1->dblPort2VKB = sqrt(KB1);
			obj->clsPipe2->dblPort1VKA = sqrt(KA2);
			obj->clsPipe3->dblPort2VKB = sqrt(KB3);
			obj->clsPipe4->dblPort2VKB = sqrt(KB4);

			break;
		case 7:
			KA1 = obj->clsPipe2->dblKAmid;
			KB2 = obj->clsPipe1->dblKBmid;
			KB3 = obj->clsPipe4->dblKBmid;
			KB4 = obj->clsPipe3->dblKBmid;
			KB1 = obj->CrossType7KB1(KA1, KB2, KB3, KB4, obj->clsPipe1->Area(obj->clsPipe2), obj->clsPipe1->dblRoughAve, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->dblRoughAve, obj->clsPipe3->Area(obj->clsPipe4), obj->clsPipe3->dblRoughAve, obj->clsPipe4->Area(obj->clsPipe1), obj->clsPipe4->dblRoughAve);

			KA2 = 1.0 * sqrt(KA1 + KB1) - KB2;
			KA3 = 1.0 * sqrt(KA1 + KB1) - KB3;
			KA4 = 1.0 * sqrt(KA1 + KB1) - KB4;
			obj->clsPipe1->dblPort2VKB = sqrt(KB1);
			obj->clsPipe2->dblPort1VKA = sqrt(KA2);
			obj->clsPipe3->dblPort1VKA = sqrt(KA3);
			obj->clsPipe4->dblPort1VKA = sqrt(KA4);

			break;

		case 8:
			KB1 = obj->clsPipe2->dblKBmid;
			KA2 = obj->clsPipe1->dblKAmid;
			KA3 = obj->clsPipe4->dblKAmid;
			KA4 = obj->clsPipe3->dblKAmid;
			KA1 = obj->CrossType8KA1(KB1, KA2, KA3, KA4, obj->clsPipe1->Area(obj->clsPipe2), obj->clsPipe1->dblRoughAve, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->dblRoughAve, obj->clsPipe3->Area(obj->clsPipe4), obj->clsPipe3->dblRoughAve, obj->clsPipe4->Area(obj->clsPipe1), obj->clsPipe4->dblRoughAve);

			KB2 = 1.0 * sqrt(KA1 + KB1) - KA2;
			KB3 = 1.0 * sqrt(KA1 + KB1) - KA3;
			KB4 = 1.0 * sqrt(KA1 + KB1) - KA4;
			obj->clsPipe1->dblPort1VKA = sqrt(KA1);
			obj->clsPipe2->dblPort2VKB = sqrt(KB2);
			obj->clsPipe3->dblPort2VKB = sqrt(KB3);
			obj->clsPipe4->dblPort2VKB = sqrt(KB4);

			break;

		case 9:
			KB1 = obj->clsPipe2->dblKBmid;
			KA2 = obj->clsPipe1->dblKAmid;
			KA3 = obj->clsPipe4->dblKAmid;
			KB4 = obj->clsPipe3->dblKBmid;
			KA1 = obj->CrossType9KA1(KB1, KA2, KA3, KB4, obj->clsPipe1->Area(obj->clsPipe2), obj->clsPipe1->dblRoughAve, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->dblRoughAve, obj->clsPipe3->Area(obj->clsPipe4), obj->clsPipe3->dblRoughAve, obj->clsPipe4->Area(obj->clsPipe1), obj->clsPipe4->dblRoughAve);
			KB2 = 1.0 * (KA1 + KB1) - KA2;
			KB3 = 1.0 * (KA1 + KB1) - KA3;
			KA4 = 1.0 * (KA1 + KB1) - KB4;
			obj->clsPipe1->dblPort1VKA = sqrt(KA1);
			obj->clsPipe2->dblPort2VKB = sqrt(KA2);
			obj->clsPipe3->dblPort2VKB = sqrt(KB3);
			obj->clsPipe4->dblPort1VKA = sqrt(KA4);

			break;
		case 10:
			KB1 = obj->clsPipe2->dblKBmid;
			KA2 = obj->clsPipe1->dblKAmid;
			KB3 = obj->clsPipe4->dblKBmid;
			KA4 = obj->clsPipe3->dblKAmid;
			KA1 = obj->CrossType10KA1(KB1, KA2, KB3, KA4, obj->clsPipe1->Area(obj->clsPipe2), obj->clsPipe1->dblRoughAve, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->dblRoughAve, obj->clsPipe3->Area(obj->clsPipe4), obj->clsPipe3->dblRoughAve, obj->clsPipe4->Area(obj->clsPipe1), obj->clsPipe4->dblRoughAve);

			KB2 = 1.0 * sqrt(KA1 + KB1) - KA2;
			KA3 = 1.0 * sqrt(KA1 + KB1) - KB3;
			KB4 = 1.0 * sqrt(KA1 + KB1) - KA4;
			obj->clsPipe1->dblPort1VKA = sqrt(KA1);
			obj->clsPipe2->dblPort2VKB = sqrt(KB2);
			obj->clsPipe3->dblPort1VKA = sqrt(KA3);
			obj->clsPipe4->dblPort2VKB = sqrt(KB4);

			break;

		case 11:
			KA1 = obj->clsPipe2->dblKAmid;
			KA2 = obj->clsPipe1->dblKAmid;
			KB3 = obj->clsPipe4->dblKBmid;
			KA4 = obj->clsPipe3->dblKAmid;
			KB1 = obj->CrossType11KA1(KA1, KA2, KB3, KA4, obj->clsPipe1->Area(obj->clsPipe2), obj->clsPipe1->dblRoughAve, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->dblRoughAve, obj->clsPipe3->Area(obj->clsPipe4), obj->clsPipe3->dblRoughAve, obj->clsPipe4->Area(obj->clsPipe1), obj->clsPipe4->dblRoughAve);
			KB2 = 1.0 * sqrt(KA1 + KB1) - KA2;
			KA3 = 1.0 * sqrt(KA1 + KB1) - KB3;
			KB4 = 1.0 * sqrt(KA1 + KB1) - KA4;
			obj->clsPipe1->dblPort2VKB = sqrt(KB1);
			obj->clsPipe2->dblPort2VKB = sqrt(KB2);
			obj->clsPipe3->dblPort1VKA = sqrt(KA3);
			obj->clsPipe4->dblPort2VKB = sqrt(KB4);

			break;
		case 12:
			KB1 = obj->clsPipe2->dblKBmid;
			KB2 = obj->clsPipe1->dblKBmid;
			KB3 = obj->clsPipe4->dblKBmid;
			KB4 = obj->clsPipe3->dblKBmid;
			KA1 = obj->CrossType12KA1(KB1, KB2, KB3, KB4, obj->clsPipe1->Area(obj->clsPipe2), obj->clsPipe1->dblRoughAve, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->dblRoughAve, obj->clsPipe3->Area(obj->clsPipe4), obj->clsPipe3->dblRoughAve, obj->clsPipe4->Area(obj->clsPipe1), obj->clsPipe4->dblRoughAve);

			KA2 = 1.0 * sqrt(KA1 + KB1) - KB2;
			KA3 = 1.0 * sqrt(KA1 + KB1) - KB3;
			KA4 = 1.0 * sqrt(KA1 + KB1) - KB4;
			obj->clsPipe1->dblPort1VKA = sqrt(KA1);
			obj->clsPipe2->dblPort1VKA = sqrt(KA2);
			obj->clsPipe3->dblPort1VKA = sqrt(KA3);
			obj->clsPipe4->dblPort1VKA = sqrt(KA4);

			break;

		case 13:
			KB1 = obj->clsPipe2->dblKBmid;
			KB2 = obj->clsPipe1->dblKBmid;
			KA3 = obj->clsPipe4->dblKAmid;
			KB4 = obj->clsPipe3->dblKBmid;
			KA1 = obj->CrossType13KA1(KB1, KB2, KA3, KB4, obj->clsPipe1->Area(obj->clsPipe2), obj->clsPipe1->dblRoughAve, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->dblRoughAve, obj->clsPipe3->Area(obj->clsPipe4), obj->clsPipe3->dblRoughAve, obj->clsPipe4->Area(obj->clsPipe1), obj->clsPipe4->dblRoughAve);

			KA2 = 1.0 * sqrt(KA1 + KB1) - KB2;
			KB3 = 1.0 * sqrt(KA1 + KB1) - KA3;
			KA4 = 1.0 * sqrt(KA1 + KB1) - KB4;
			obj->clsPipe1->dblPort1VKA = sqrt(KA1);
			obj->clsPipe2->dblPort1VKA = sqrt(KA2);
			obj->clsPipe3->dblPort2VKB = sqrt(KB3);
			obj->clsPipe4->dblPort1VKA = sqrt(KA4);

			break;

		case 14:
			KB1 = obj->clsPipe2->dblKBmid;
			KB2 = obj->clsPipe1->dblKBmid;
			KB3 = obj->clsPipe4->dblKBmid;
			KA4 = obj->clsPipe3->dblKAmid;
			KA1 = obj->CrossType14KA1(KB1, KB2, KB3, KA4, obj->clsPipe1->Area(obj->clsPipe2), obj->clsPipe1->dblRoughAve, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->dblRoughAve, obj->clsPipe3->Area(obj->clsPipe4), obj->clsPipe3->dblRoughAve, obj->clsPipe4->Area(obj->clsPipe1), obj->clsPipe4->dblRoughAve);

			KA2 = 1.0 * sqrt(KA1 + KB1) - KB2;
			KA3 = 1.0 * sqrt(KA1 + KB1) - KB3;
			KB4 = 1.0 * sqrt(KA1 + KB1) - KA4;
			obj->clsPipe1->dblPort1VKA = sqrt(KA1);
			obj->clsPipe2->dblPort1VKA = sqrt(KA2);
			obj->clsPipe3->dblPort1VKA = sqrt(KA3);
			obj->clsPipe4->dblPort2VKB = sqrt(KB4);

			break;

		case 15:
			KA1 = obj->clsPipe2->dblKAmid;
			KA2 = obj->clsPipe1->dblKAmid;
			KA3 = obj->clsPipe4->dblKAmid;
			KB4 = obj->clsPipe3->dblKBmid;
			KB1 = obj->CrossType15KB1(KA1, KA2, KA3, KB4, obj->clsPipe1->Area(obj->clsPipe2), obj->clsPipe1->dblRoughAve, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->dblRoughAve, obj->clsPipe3->Area(obj->clsPipe4), obj->clsPipe3->dblRoughAve, obj->clsPipe4->Area(obj->clsPipe1), obj->clsPipe4->dblRoughAve);
			KB2 = 1.0 * sqrt(KA1 + KB1) - KA2;
			KB3 = 1.0 * sqrt(KA1 + KB1) - KA3;
			KA4 = 1.0 * sqrt(KA1 + KB1) - KB4;
			obj->clsPipe1->dblPort2VKB = sqrt(KB1);
			obj->clsPipe2->dblPort2VKB = sqrt(KB2);
			obj->clsPipe3->dblPort2VKB = sqrt(KB3);
			obj->clsPipe4->dblPort1VKA = sqrt(KA4);

			break;

		case 16:


			KB1 = obj->clsPipe2->dblKBmid;
			KB2 = obj->clsPipe1->dblKBmid;
			KA3 = obj->clsPipe4->dblKAmid;
			KA4 = obj->clsPipe3->dblKAmid;
			KA1 = obj->CrossType16KA1(KB1, KB2, KA3, KA4, obj->clsPipe1->Area(obj->clsPipe2), obj->clsPipe1->dblRoughAve, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->dblRoughAve, obj->clsPipe3->Area(obj->clsPipe4), obj->clsPipe3->dblRoughAve, obj->clsPipe4->Area(obj->clsPipe1), obj->clsPipe4->dblRoughAve);

			KA2 = 1.0 * sqrt(KA1 + KB1) - KB2;
			KB3 = 1.0 * sqrt(KA1 + KB1) - KA3;
			KB4 = 1.0 * sqrt(KA1 + KB1) - KA4;

			obj->clsPipe1->dblPort1VKA = sqrt(KA1);
			obj->clsPipe2->dblPort1VKA = sqrt(KA2);
			obj->clsPipe3->dblPort2VKB = sqrt(KB3);
			obj->clsPipe4->dblPort2VKB = sqrt(KB4);

			break;
		default:printf("四通类型错误.\n");

		}

		obj->dblErrP = MyCurP - obj->Ports[4].dblP;





	}

	void DoHydraulicBack(WaterCrossStruct*) {

	}





	double CrossType1KB1(double dblKA1, double dblKA2, double dblKA3, double dblKB4, double dblA1, double dblAS1, double dblA2, double dblAS2, double dblA3, double dblAS3, double dblA4, double dblAS4) {

		double dblKB1;
		double fengzi;
		double fengmu;
		fengzi = 1.0 * dblKA1 * sqrt(dblA1 / dblAS1 - dblA2 / dblAS2 - dblA3 / dblAS3 - dblA4 / dblAS4) + 2 * sqrt(dblKA2 * dblA2 / dblAS2 + dblKA3 * dblA3 / dblAS3 + dblKB4 * dblA4 / dblAS4);
		fengmu = 1.0 * dblA1 / dblAS1 + dblA2 / dblAS2 + dblA3 / dblAS3 + dblA4 / dblAS4;
		dblKB1 = fengzi / fengmu;
		return dblKB1;

	}

	double CrossType2KB1(double dblKA1, double dblKA2, double dblKB3, double dblKA4, double dblA1, double dblAS1, double dblA2, double dblAS2, double dblA3, double dblAS3, double dblA4, double dblAS4) {
		double dblKB1;
		double fengzi;
		double fengmu;
		fengzi = 1.0 * dblKA1 * sqrt(dblA1 / dblAS1 - dblA2 / dblAS2 - dblA3 / dblAS3 - dblA4 / dblAS4) + 2 * sqrt(dblKA2 * dblA2 / dblAS2 + dblKB3 * dblA3 / dblAS3 + dblKA4 * dblA4 / dblAS4);
		fengmu = 1.0 * dblA1 / dblAS1 + dblA2 / dblAS2 + dblA3 / dblAS3 + dblA4 / dblAS4;
		dblKB1 = fengzi / fengmu;
		return dblKB1;

	}

	double CrossType3KB1(double dblKA1, double dblKA2, double dblKB3, double dblKB4, double dblA1, double dblAS1, double dblA2, double dblAS2, double dblA3, double dblAS3, double dblA4, double dblAS4) {

		double dblKB1;
		double fengzi;
		double fengmu;
		fengzi = 1.0 * dblKA1 * sqrt(dblA1 / dblAS1 - dblA2 / dblAS2 - dblA3 / dblAS3 - dblA4 / dblAS4) + 2 * sqrt(dblKA2 * dblA2 / dblAS2 + dblKB3 * dblA3 / dblAS3 + dblKB4 * dblA4 / dblAS4);
		fengmu = 1.0 * dblA1 / dblAS1 + dblA2 / dblAS2 + dblA3 / dblAS3 + dblA4 / dblAS4;
		dblKB1 = fengzi / fengmu;
		return dblKB1;
	}

	double CrossType4KB1(double dblKA1, double dblKB2, double dblKA3, double dblKA4, double dblA1, double dblAS1, double dblA2, double dblAS2, double dblA3, double dblAS3, double dblA4, double dblAS4) {
		double dblKB1;
		double fengzi;
		double fengmu;
		fengzi = dblKA1 * sqrt(dblA1 / dblAS1 - dblA2 / dblAS2 - dblA3 / dblAS3 - dblA4 / dblAS4) + 2 * sqrt(dblKB2 * dblA2 / dblAS2 + dblKA3 * dblA3 / dblAS3 + dblKA4 * dblA4 / dblAS4);
		fengmu = dblA1 / dblAS1 + dblA2 / dblAS2 + dblA3 / dblAS3 + dblA4 / dblAS4;
		dblKB1 = fengzi / fengmu;
		return dblKB1;
	}

	double CrossType5KB1(double dblKA1, double dblKB2, double dblKA3, double dblKB4, double dblA1, double dblAS1, double dblA2, double dblAS2, double dblA3, double dblAS3, double dblA4, double dblAS4) {

		double dblKB1;
		double fengzi;
		double fengmu;
		fengzi = dblKA1 * sqrt(dblA1 / dblAS1 - dblA2 / dblAS2 - dblA3 / dblAS3 - dblA4 / dblAS4) + 2 * sqrt(dblKB2 * dblA2 / dblAS2 + dblKA3 * dblA3 / dblAS3 + dblKB4 * dblA4 / dblAS4);
		fengmu = dblA1 / dblAS1 + dblA2 / dblAS2 + dblA3 / dblAS3 + dblA4 / dblAS4;
		dblKB1 = fengzi / fengmu;
		return dblKB1;

	}

	double CrossType6KB1(double dblKA1, double dblKB2, double dblKB3, double dblKA4, double dblA1, double dblAS1, double dblA2, double dblAS2, double dblA3, double dblAS3, double dblA4, double dblAS4) {

		double dblKB1;
		double fengzi;
		double fengmu;
		fengzi = dblKA1 * sqrt(dblA1 / dblAS1 - dblA2 / dblAS2 - dblA3 / dblAS3 - dblA4 / dblAS4) + 2 * sqrt(dblKB2 * dblA2 / dblAS2 + dblKB3 * dblA3 / dblAS3 + dblKA4 * dblA4 / dblAS4);
		fengmu = dblA1 / dblAS1 + dblA2 / dblAS2 + dblA3 / dblAS3 + dblA4 / dblAS4;
		dblKB1 = fengzi / fengmu;
		return dblKB1;

	}

	double CrossType7KB1(double dblKA1, double dblKB2, double dblKB3, double dblKB4, double dblA1, double dblAS1, double dblA2, double dblAS2, double dblA3, double dblAS3, double dblA4, double dblAS4) {
		double dblKB1;
		double fengzi;
		double fengmu;
		fengzi = dblKA1 * sqrt(dblA1 / dblAS1 - dblA2 / dblAS2 - dblA3 / dblAS3 - dblA4 / dblAS4) + 2 * sqrt(dblKB2 * dblA2 / dblAS2 + dblKB3 * dblA3 / dblAS3 + dblKB4 * dblA4 / dblAS4);
		fengmu = dblA1 / dblAS1 + dblA2 / dblAS2 + dblA3 / dblAS3 + dblA4 / dblAS4;
		dblKB1 = fengzi / fengmu;
		return dblKB1;
	}

	double CrossType8KA1(double dblKB1, double dblKA2, double dblKA3, double dblKA4, double dblA1, double dblAS1, double dblA2, double dblAS2, double dblA3, double dblAS3, double dblA4, double dblAS4) {

		double dblKA1;
		double fengzi;
		double fengmu;
		fengzi = dblKB1 * sqrt(dblA1 / dblAS1 - dblA2 / dblAS2 - dblA3 / dblAS3 - dblA4 / dblAS4) + 2 * sqrt(dblKA2 * dblA2 / dblAS2 + dblKA3 * dblA3 / dblAS3 + dblKA4 * dblA4 / dblAS4);
		fengmu = dblA1 / dblAS1 + dblA2 / dblAS2 + dblA3 / dblAS3 + dblA4 / dblAS4;
		dblKA1 = fengzi / fengmu;
		return dblKA1;
	}

	double CrossType9KA1(double dblKB1, double dblKA2, double dblKA3, double dblKB4, double dblA1, double dblAS1, double dblA2, double dblAS2, double dblA3, double dblAS3, double dblA4, double dblAS4) {
		double dblKA1;
		double fengzi;
		double fengmu;
		fengzi = dblKB1 * sqrt(dblA1 / dblAS1 - dblA2 / dblAS2 - dblA3 / dblAS3 - dblA4 / dblAS4) + 2 * sqrt(dblKA2 * dblA2 / dblAS2 + dblKA3 * dblA3 / dblAS3 + dblKB4 * dblA4 / dblAS4);
		fengmu = dblA1 / dblAS1 + dblA2 / dblAS2 + dblA3 / dblAS3 + dblA4 / dblAS4;
		dblKA1 = fengzi / fengmu;
		return dblKA1;


	}

	double CrossType10KA1(double dblKB1, double dblKA2, double dblKB3, double dblKA4, double dblA1, double dblAS1, double dblA2, double dblAS2, double dblA3, double dblAS3, double dblA4, double dblAS4) {

		double dblKA1;
		double fengzi;
		double fengmu;
		fengzi = dblKB1 * sqrt(dblA1 / dblAS1 - dblA2 / dblAS2 - dblA3 / dblAS3 - dblA4 / dblAS4) + 2 * sqrt(dblKA2 * dblA2 / dblAS2 + dblKB3 * dblA3 / dblAS3 + dblKA4 * dblA4 / dblAS4);
		fengmu = dblA1 / dblAS1 + dblA2 / dblAS2 + dblA3 / dblAS3 + dblA4 / dblAS4;
		dblKA1 = fengzi / fengmu;
		return dblKA1;

	}

	double CrossType11KA1(double dblKB1, double dblKA2, double dblKB3, double dblKB4, double dblA1, double dblAS1, double dblA2, double dblAS2, double dblA3, double dblAS3, double dblA4, double dblAS4) {

		double dblKA1;
		double fengzi;
		double fengmu;
		fengzi = dblKB1 * sqrt(dblA1 / dblAS1 - dblA2 / dblAS2 - dblA3 / dblAS3 - dblA4 / dblAS4) + 2 * sqrt(dblKA2 * dblA2 / dblAS2 + dblKB3 * dblA3 / dblAS3 + dblKB4 * dblA4 / dblAS4);
		fengmu = dblA1 / dblAS1 + dblA2 / dblAS2 + dblA3 / dblAS3 + dblA4 / dblAS4;
		dblKA1 = fengzi / fengmu;
		return dblKA1;
	}

	double CrossType12KA1(double dblKB1, double dblKB2, double dblKA3, double dblKA4, double dblA1, double dblAS1, double dblA2, double dblAS2, double dblA3, double dblAS3, double dblA4, double dblAS4) {

		double dblKA1;
		double fengzi;
		double fengmu;
		fengzi = dblKB1 * sqrt(dblA1 / dblAS1 - dblA2 / dblAS2 - dblA3 / dblAS3 - dblA4 / dblAS4) + 2 * sqrt(dblKB2 * dblA2 / dblAS2 + dblKA3 * dblA3 / dblAS3 + dblKA4 * dblA4 / dblAS4);
		fengmu = dblA1 / dblAS1 + dblA2 / dblAS2 + dblA3 / dblAS3 + dblA4 / dblAS4;
		dblKA1 = fengzi / fengmu;
		return dblKA1;
	}

	double CrossType13KA1(double dblKB1, double dblKB2, double dblKA3, double dblKB4, double dblA1, double dblAS1, double dblA2, double dblAS2, double dblA3, double dblAS3, double dblA4, double dblAS4) {

		double dblKA1;
		double fengzi;
		double fengmu;
		fengzi = dblKB1 * sqrt(dblA1 / dblAS1 - dblA2 / dblAS2 - dblA3 / dblAS3 - dblA4 / dblAS4) + 2 * sqrt(dblKB2 * dblA2 / dblAS2 + dblKA3 * dblA3 / dblAS3 + dblKB4 * dblA4 / dblAS4);
		fengmu = dblA1 / dblAS1 + dblA2 / dblAS2 + dblA3 / dblAS3 + dblA4 / dblAS4;
		dblKA1 = fengzi / fengmu;
		return dblKA1;
	}

	double CrossType14KA1(double dblKB1, double dblKB2, double dblKB3, double dblKA4, double dblA1, double dblAS1, double dblA2, double dblAS2, double dblA3, double dblAS3, double dblA4, double dblAS4) {

		double dblKA1;
		double fengzi;
		double fengmu;
		fengzi = dblKB1 * sqrt(dblA1 / dblAS1 - dblA2 / dblAS2 - dblA3 / dblAS3 - dblA4 / dblAS4) + 2 * sqrt(dblKB2 * dblA2 / dblAS2 + dblKB3 * dblA3 / dblAS3 + dblKA4 * dblA4 / dblAS4);
		fengmu = dblA1 / dblAS1 + dblA2 / dblAS2 + dblA3 / dblAS3 + dblA4 / dblAS4;
		dblKA1 = fengzi / fengmu;
		return dblKA1;
	}

	double CrossType15KB1(double dblKA1, double dblKA2, double dblKA3, double dblKA4, double dblA1, double dblAS1, double dblA2, double dblAS2, double dblA3, double dblAS3, double dblA4, double dblAS4) {

		double dblKB1;
		double fengzi;
		double fengmu;
		fengzi = dblKA1 * sqrt(dblA1 / dblAS1 - dblA2 / dblAS2 - dblA3 / dblAS3 - dblA4 / dblAS4) + 2 * sqrt(dblKA2 * dblA2 / dblAS2 + dblKA3 * dblA3 / dblAS3 + dblKA4 * dblA4 / dblAS4);
		fengmu = dblA1 / dblAS1 + dblA2 / dblAS2 + dblA3 / dblAS3 + dblA4 / dblAS4;
		dblKB1 = fengzi / fengmu;
		return dblKB1;
	}
	double CrossType16KA1(double dblKB1, double dblKB2, double dblKB3, double dblKB4, double dblA1, double dblAS1, double dblA2, double dblAS2, double dblA3, double dblAS3, double dblA4, double dblAS4) {

		double dblKA1;
		double fengzi;
		double fengmu;
		fengzi = dblKB1 * sqrt(dblA1 / dblAS1 - dblA2 / dblAS2 - dblA3 / dblAS3 - dblA4 / dblAS4) + 2 * sqrt(dblKB2 * dblA2 / dblAS2 + dblKB3 * dblA3 / dblAS3 + dblKB4 * dblA4 / dblAS4);
		fengmu = dblA1 / dblAS1 + dblA2 / dblAS2 + dblA3 / dblAS3 + dblA4 / dblAS4;
		dblKA1 = fengzi / fengmu;
		return dblKA1;
	}

	double DoKA(WaterCrossStruct*, double, double, double, double, double, double, double, double) {

		return 0;
	}

	double DoKB(WaterCrossStruct*, double, double, double, double, double, double, double, double) {

		return 0;
	}

	void RefreshHydraulic(WaterCrossStruct* obj) {

		if (obj->clsPipe1->Ports[2].ConnectPieceNo == obj->intNum) {
			obj->Ports[2].dblP = obj->clsPipe1->Ports[1].dblP;
			obj->Ports[2].dblM = -1.0 * obj->clsPipe1->Ports[1].dblM;
			obj->Ports[2].dblU = -1.0 * obj->clsPipe1->dblUmid;

		}
		else {
			obj->Ports[1].dblP = obj->clsPipe1->Ports[2].dblP;
			obj->Ports[1].dblM = obj->clsPipe1->Ports[2].dblM;
			obj->Ports[1].dblU = obj->clsPipe1->dblUmid;

		}

		if (obj->clsPipe2->Ports[2].ConnectPieceNo == obj->intNum) {
			obj->Ports[2].dblP = obj->clsPipe2->Ports[1].dblP;
			obj->Ports[2].dblM = -1.0 * obj->clsPipe2->Ports[1].dblM;
			obj->Ports[2].dblU = -1.0 * obj->clsPipe2->dblUmid;

		}
		else {
			obj->Ports[1].dblP = obj->clsPipe2->Ports[2].dblP;
			obj->Ports[1].dblM = obj->clsPipe2->Ports[2].dblM;
			obj->Ports[1].dblU = obj->clsPipe2->dblUmid;

		}

		if (obj->clsPipe3->Ports[3].ConnectPieceNo == obj->intNum) {
			obj->Ports[3].dblP = obj->clsPipe3->Ports[1].dblP;
			obj->Ports[3].dblM = -1.0 * obj->clsPipe3->Ports[1].dblM;
			obj->Ports[3].dblU = -1.0 * obj->clsPipe3->dblUmid;

		}
		else {
			obj->Ports[1].dblP = obj->clsPipe3->Ports[2].dblP;
			obj->Ports[1].dblM = obj->clsPipe3->Ports[2].dblM;
			obj->Ports[1].dblU = obj->clsPipe3->dblUmid;

		}


		if (obj->clsPipe4->Ports[4].ConnectPieceNo == obj->intNum) {
			obj->Ports[1].dblP = obj->clsPipe4->Ports[2].dblP;
			obj->Ports[1].dblM = obj->clsPipe4->Ports[2].dblM;
			obj->Ports[1].dblU = obj->clsPipe4->dblUmid;

		}
		else {
			obj->Ports[4].dblP = obj->clsPipe4->Ports[1].dblP;
			obj->Ports[4].dblM = -1.0 * obj->clsPipe4->Ports[1].dblM;
			obj->Ports[4].dblU = -1.0 * obj->clsPipe4->dblUmid;

		}

	}

	double DoThermal(WaterCrossStruct*) {

		return 0;
	}

	double TestConnection(WaterCrossStruct*) {

		return 0;
	}

	double TestTopology(WaterCrossStruct*) {

		return 0;
	}


};



#endif