#pragma once
#ifndef __PUMP_STRUCT_H__
#define __PUMP_STRUCT_H__
#include"PipeStruct.h"
#include"math.h"
struct PumpStruct {
	struct PipePort {
		double Dn;
		int JoinCode;
		int JoinPortNum;
		double en_pressure;
		double en_velocity;
		double en_temperature;
		double en_quality;
		double en_density;
	};
	char* pumpName;
	int pumpCode;
	int pumpType;
	PipePort Ports[3];
	PipeStruct* joinPipe1;
	PipeStruct* joinPipe2;
	double pumpA2;
	double pumpA2;
	double pumpA0;
	double pumpSpeedN;
	double pumpSpeedN0;
	char pumpConnected;
	int OperationNumber;
	int TubeNum;
	int TubeType;



	double DP(PumpStruct*) {


		return 0;
	}
	double Rm(PumpStruct* obj) {

		return (obj->pumpA2 / obj->joinPipe1->diam / obj->Ports[1].en_quality * obj->joinPipe1->diam * obj->Ports[2].en_quality +
			obj->pumpA2 / obj->joinPipe1->diam / obj->Ports[1].en_quality * (obj->pumpSpeedN / obj->pumpSpeedN0) + obj->pumpA0 / (obj->pumpSpeedN / obj->pumpSpeedN0));
	}

	void New1(PumpStruct*) {

	}
	void New2(PumpStruct* object, int intThePumpOLGNum, char* strThePumpOLGName, int intThePumpOLGConnPiece1, int intThePumpOLGConnPort1,
		int intThePumpOLGConnPiece2, int intThePumpOLGConnPort2, double pumpA2, double pumpA1,
		double pumpA0, double dblFr0, double dblFr, int intOPN) {
		object->pumpCode = intThePumpOLGNum;


		object->Ports[1].JoinCode = intThePumpOLGConnPiece1;
		object->Ports[1].JoinPortNum = intThePumpOLGConnPort1;
		object->Ports[1].en_pressure = Patm;
		object->Ports[1].en_temperature = Tair;
		object->Ports[1].en_quality = 0.0;
		object->Ports[2].JoinCode = intThePumpOLGConnPiece2;
		object->Ports[2].JoinPortNum = intThePumpOLGConnPort2;
		object->Ports[2].en_pressure = Patm;
		object->Ports[2].en_temperature = Tair;
		object->Ports[2].en_quality = 0.0;

		object->pumpA2 = pumpA2;
		object->pumpA2 = pumpA2;
		object->pumpA0 = pumpA0;
		object->pumpSpeedN = dblFr;
		object->pumpSpeedN0 = dblFr0;
		object->OperationNumber = intOPN;
		object->TubeType = PumpOLG;
		object->TubeNum = intThePumpOLGNum;

	}

	void Host_Init(PumpStruct* obj, PipeStruct* pipe1, PipeStruct* pipe2) {

		obj->joinPipe1 = pipe1;
		obj->joinPipe2 = pipe2;
	}



	void Init(PumpStruct* obj, PipeStruct* pipe1, PipeStruct* pipe2) {

		obj->joinPipe1 = pipe1;
		obj->joinPipe2 = pipe2;
		obj->Ports[1].Dn = pipe1->diam;
		obj->Ports[2].Dn = pipe2->diam;
		if (pipe1->elev2 != pipe2->elev1) {
			printf("上下点位管道高度不一致！\n", obj->pumpCode);
		}
		obj->CheckConnType(obj);
		switch (obj->pumpType) {
		case 1:
			obj->Ports[1].en_pressure = pipe1->Ports[2].en_pressure;
			obj->Ports[1].en_velocity = pipe1->Ports[2].en_velocity;
			obj->Ports[1].en_temperature = pipe1->Ports[2].en_temperature;
			obj->Ports[2].en_pressure = pipe2->Ports[1].en_pressure;
			obj->Ports[2].en_velocity = pipe2->Ports[1].en_velocity;
			obj->Ports[2].en_temperature = pipe2->Ports[1].en_temperature;
			break;
		case 2:
			;
			break;
		case 3:
			;
			break;
		case 4:
			;
			break;
		}



	}
	void Host_CheckConnType(PumpStruct* obj) {
		if (obj->Ports[1].JoinPortNum == 1 && obj->Ports[2].JoinPortNum == 1) {
			obj->pumpType = 1;
		}
		else if (obj->Ports[1].JoinPortNum == 1 && obj->Ports[2].JoinPortNum == 2) {
			obj->pumpType = 2;
		}
		else if (obj->Ports[1].JoinPortNum == 2 && obj->Ports[2].JoinPortNum == 1) {
			obj->pumpType = 3;
		}
		else if (obj->Ports[1].JoinPortNum == 2 && obj->Ports[2].JoinPortNum == 2) {
			obj->pumpType = 4;
		}
	}

	void CheckConnType(PumpStruct* obj) {
		if (obj->Ports[1].JoinPortNum == 1 && obj->Ports[2].JoinPortNum == 1) {
			obj->pumpType = 1;
		}
		else if (obj->Ports[1].JoinPortNum == 1 && obj->Ports[2].JoinPortNum == 2) {
			obj->pumpType = 2;
		}
		else if (obj->Ports[1].JoinPortNum == 2 && obj->Ports[2].JoinPortNum == 1) {
			obj->pumpType = 3;
		}
		else if (obj->Ports[1].JoinPortNum == 2 && obj->Ports[2].JoinPortNum == 2) {
			obj->pumpType = 4;
		}
	}
	void Runhyd(PumpStruct* obj) {
		double KA1;
		double KA2;
		double KB1;
		double KB2;
		double Vc;
		double Rho1, Rho2, Area1, Area2, As1, As2;
		double A, B, C, det;
		Rho1 = obj->joinPipe1->densityMid;
		Rho2 = obj->joinPipe2->densityMid;
		Area1 = obj->joinPipe1->Area(obj->joinPipe2);
		Area2 = obj->joinPipe2->Area(obj->joinPipe1);
		As1 = sqrt(obj->joinPipe2->speedOfSound);
		As2 = sqrt(obj->joinPipe1->speedOfSound);

		switch (obj->pumpType) {
		case 1:
			KA1 = obj->joinPipe2->fkaMid;
			KB2 = obj->joinPipe1->fkbMid;
			A = obj->pumpA2 * obj->pumpA2 * (Area1 * obj->OperationNumber) / (Area1 / obj->OperationNumber);
			B = obj->pumpA2 * obj->pumpA2 * (Area1 * obj->OperationNumber) / (obj->pumpSpeedN * obj->pumpSpeedN0);
			C = obj->pumpA0 * obj->pumpA0 * (obj->pumpSpeedN / obj->pumpSpeedN0) / (obj->pumpSpeedN * obj->pumpSpeedN0);

			det = 1.0 * B * B * A * C - 4 * B * A * C;
			if (det > 0) {
				double temp1 = 1.0 * (-B - sqrt(B * B - 4 * A * C)) / (2 * A);
				double temp2 = 1.0 * (-B + sqrt(B * B - 4 * A * C)) / (2 * A);
				Vc = temp1 < temp2 ? temp1 : temp2;
			}
			else
			{
				Vc = 0;
			}
			if (Vc < 0) {
				Vc = 0;
			}
			KB1 = KA1 - 2 * Rho1 * Vc / (Area1 * Area2);
			KA2 = KB2 + 2 * Rho1 * Vc * KA1 / (Area1 * Area2);
			obj->joinPipe1->port2VKB = sqrt(KB1);
			obj->joinPipe2->port1VKA = sqrt(KA2);
			break;
		}
		obj->Ports[1].en_density = obj->joinPipe1->densityMid / obj->OperationNumber;
		obj->Ports[2].en_density = obj->joinPipe2->densityMid / obj->OperationNumber;
		obj->Ports[1].en_quality = obj->Ports[1].en_density / obj->Ports[1].en_velocity;
		obj->Ports[2].en_quality = obj->Ports[2].en_density / obj->Ports[2].en_velocity;
	}
	void SwapVal(PumpStruct* obj) {

		if (obj->joinPipe1->Ports[1].JoinCode == obj->pumpCode) {
			obj->Ports[1].en_pressure = obj->joinPipe1->Ports[1].en_pressure;
			obj->Ports[1].en_velocity = obj->joinPipe1->uMid;

		}
		else {
			obj->Ports[2].en_pressure = obj->joinPipe1->Ports[2].en_pressure;
			obj->Ports[2].en_velocity = -1.0 * obj->joinPipe1->uMid;

		}
		if (obj->joinPipe2->Ports[1].JoinCode == obj->pumpCode) {
			obj->Ports[2].en_pressure = obj->joinPipe2->Ports[2].en_pressure;
			obj->Ports[2].en_velocity = obj->joinPipe2->uMid;

		}
		else {
			obj->Ports[1].en_pressure = obj->joinPipe2->Ports[2].en_pressure;
			obj->Ports[1].en_velocity = -1.0 * obj->joinPipe2->uMid;
		}

	}
	void RunThermal(PumpStruct*) {

	}
	void TestConnection(PumpStruct*) {

	}


};


#endif