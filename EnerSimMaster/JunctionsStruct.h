#pragma once
#ifndef __JUNCTIONS_STRUCT_H__
#define __JUNCTIONS_STRUCT_H__
#include"PipeStruct.h"
#include"PipeComponentsTypeENUM.h"

struct PlugsStruct {
	char* strName;
	int intNumber;
	int intConnectedPipeNumber;
	int intConnectedPortNumber;
	double en_pressure;
	double en_quality;
	double en_velocity;
	double en_temperature;
	double en_elev;
	double en_nor_v;
	PipeStruct* joinPipe1;
	char blnConnected;
	int TubeNum;
	int TubeType;
	void New1(PlugsStruct*) {

	}
	void New2(PlugsStruct* object, int PlugsCode, char* PlugsName, int PlugsJoin1, int PlugsPort1) {

		object->intNumber = PlugsCode;

		object->intConnectedPipeNumber = PlugsJoin1;
		object->intConnectedPortNumber = PlugsPort1;
		object->TubeType = Plugs;
		object->TubeNum = PlugsCode;


	}

	void Init(PlugsStruct* obj, PipeStruct* pipe1) {
		obj->joinPipe1 = pipe1;



	}
	void Runhyd(PlugsStruct* obj) {
		obj->en_nor_v = 0.0;
		obj->en_velocity = 0.0;
		obj->joinPipe1->Ports[1].en_density = obj->joinPipe1->Ports[1].en_velocity / obj->joinPipe1->Ports[1].en_quality + obj->joinPipe1->Ports[2].en_velocity / obj->joinPipe1->Ports[2].en_quality;
		obj->joinPipe1->Ports[1].Pfixed = 'Y';
		obj->joinPipe1->Ports[1].Ufixed = 'N';

	}
	void SwapVal(PlugsStruct* obj) {
		obj->en_quality = obj->joinPipe1->Ports[1].en_density;
		obj->en_pressure = 0.0;
	}
	void RunThermal(PlugsStruct*) {

	}
	void TestConnection(PlugsStruct*) {

	}

	void TestTopology(PlugsStruct*) {

	}
};

struct TwowayStruct {
	struct PipePort {
		double Dn;
		int JoinCode;
		int ConnectPortNo;
		double en_pressure;
		double en_velocity;
		double en_temperature;
		double en_quality;
		double dblV;
	};
	char* strName;
	int intNum;
	int intMyType;
	PipePort Ports[3];
	PipeStruct* joinPipe1;
	PipeStruct* clsPipe2;
	double dblTmix;
	double dblErrP;
	char blnConnected;//y  or   c
	int TubeNum;
	int TubeType;



	void New1(TwowayStruct*) {

	}
	void New2(TwowayStruct* obj, int intTheTwoWayNum, char* strTheTwoWayName, int intTheTwoWayConnPiece1, int intTheTwoWayConnPort1, int intTheTwoWayConnPiece2, int intTheTwoWayConnPort2) {

		obj->intNum = intTheTwoWayNum;

		obj->intMyType = 1;
		obj->Ports[1].JoinCode = intTheTwoWayConnPiece1;
		obj->Ports[1].ConnectPortNo = intTheTwoWayConnPort1;
		obj->Ports[1].en_pressure = Patm;
		obj->Ports[1].en_velocity = 0.0;
		obj->Ports[1].en_temperature = defTwater;
		obj->Ports[2].JoinCode = intTheTwoWayConnPiece2;
		obj->Ports[2].ConnectPortNo = intTheTwoWayConnPort2;
		obj->Ports[2].en_pressure = Patm;
		obj->Ports[2].en_velocity = 0.0;
		obj->Ports[2].en_temperature = defTwater;
		obj->TubeType = Twoway;
		obj->TubeNum = intTheTwoWayNum;


	}

	void Init(TwowayStruct* obj, PipeStruct* pipe1, PipeStruct* pipe2) {
		obj->joinPipe1 = pipe1;
		obj->clsPipe2 = pipe2;
		obj->CheckTwoWayType(obj);
		if (obj->Ports[1].ConnectPortNo == 1) {
			obj->Ports[1].en_temperature = pipe1->Ports[1].en_temperature;
		}
		else {
			obj->Ports[1].en_temperature = pipe1->Ports[2].en_temperature;
		}

		if (obj->Ports[2].ConnectPortNo == 1) {
			obj->Ports[2].en_temperature = pipe2->Ports[1].en_temperature;
		}
		else {
			obj->Ports[2].en_temperature = pipe2->Ports[2].en_temperature;
		}

		switch (obj->intMyType) {
		case 1:
			obj->Ports[2].en_pressure = pipe1->Ports[2].en_pressure;
			obj->Ports[2].en_velocity = pipe1->Ports[2].en_velocity;
			obj->Ports[2].en_temperature = pipe1->Ports[2].en_temperature;
			obj->Ports[1].en_pressure = pipe2->Ports[1].en_pressure;
			obj->Ports[1].en_velocity = pipe2->Ports[1].en_velocity;
			obj->Ports[1].en_temperature = pipe2->Ports[1].en_temperature;
			break;
		case 2:
			obj->Ports[2].en_pressure = pipe1->Ports[1].en_pressure;
			obj->Ports[2].en_velocity = pipe1->Ports[1].en_velocity;
			obj->Ports[2].en_temperature = pipe1->Ports[1].en_temperature;
			obj->Ports[1].en_pressure = pipe2->Ports[2].en_pressure;
			obj->Ports[1].en_velocity = pipe2->Ports[2].en_velocity;
			obj->Ports[1].en_temperature = pipe2->Ports[2].en_temperature;
			break;
		case 3:
			obj->Ports[2].en_pressure = pipe1->Ports[2].en_pressure;
			obj->Ports[2].en_velocity = pipe1->Ports[2].en_velocity;
			obj->Ports[2].en_temperature = pipe1->Ports[2].en_temperature;
			obj->Ports[1].en_pressure = pipe2->Ports[2].en_pressure;
			obj->Ports[1].en_velocity = pipe2->Ports[2].en_velocity;
			obj->Ports[1].en_temperature = pipe2->Ports[2].en_temperature;
			break;
		case 4:
			obj->Ports[2].en_pressure = pipe1->Ports[1].en_pressure;
			obj->Ports[2].en_velocity = pipe1->Ports[1].en_velocity;
			obj->Ports[2].en_temperature = pipe1->Ports[1].en_temperature;
			obj->Ports[1].en_pressure = pipe2->Ports[1].en_pressure;
			obj->Ports[1].en_velocity = pipe2->Ports[1].en_velocity;
			obj->Ports[1].en_temperature = pipe2->Ports[1].en_temperature;
			break;
		}



	}

	double TwoWayType1KB1(double dblKA1, double dblKB2, double dblA1, double dblAS1, double dblA2, double dblAS2) {

		double dblKB1;
		double fengzi;
		double fengmu;
		fengzi = 1.0 * (dblKA1 * (dblA1 / dblAS1 - dblA2) + 2 * (dblKB2 / dblAS2));
		fengmu = 1.0 * (dblA1 / dblAS1 + dblA2);
		dblKB1 = fengzi / fengmu;
		return dblKB1;
	}

	double TwoWayType2KA1(double dblKB1, double dblKA2, double dblA1, double dblAS1, double dblA2, double dblAS2) {
		double dblKA1;
		double fengzi;
		double fengmu;
		fengzi = 1.0 * (dblKB1 * (dblA1 / dblAS1 - dblA2) + 2 * (dblKA2 / dblAS2));
		fengmu = 1.0 * (dblA1 / dblAS1 + dblA2);
		dblKA1 = fengzi / fengmu;
		return dblKA1;
	}

	double TwoWayType3KB1(double dblKA1, double dblKA2, double dblA1, double dblAS1, double dblA2, double dblAS2) {
		double dblKB1;
		double fengzi;
		double fengmu;
		fengzi = 1.0 * (dblKA1 * (dblA1 / dblAS1 - dblA2) + 2 * (dblKA2 / dblAS2));
		fengmu = 1.0 * (dblA1 / dblAS1 + dblA2);
		dblKB1 = fengzi / fengmu;
		return dblKB1;
	}

	double TwoWayType4KA1(double dblKB1, double dblKB2, double dblA1, double dblAS1, double dblA2, double dblAS2) {
		double dblKA1;
		double fengzi;
		double fengmu;
		fengzi = 1.0 * (dblKB1 * (dblA1 / dblAS1 - dblA2) + 2 * (dblKB2 / dblAS2));
		fengmu = 1.0 * (dblA1 / dblAS1 + dblA2);
		dblKA1 = fengzi / fengmu;
		return dblKA1;
	}
	void CheckTwoWayType(TwowayStruct* obj) {
		if (obj->Ports[1].ConnectPortNo == 1 && obj->Ports[2].ConnectPortNo == 1) {
			obj->intMyType = 1;
		}
		else if (obj->Ports[1].ConnectPortNo == 1 && obj->Ports[2].ConnectPortNo == 2) {
			obj->intMyType = 2;
		}
		else if (obj->Ports[1].ConnectPortNo == 2 && obj->Ports[2].ConnectPortNo == 1) {
			obj->intMyType = 3;
		}
		else if (obj->Ports[1].ConnectPortNo == 2 && obj->Ports[2].ConnectPortNo == 2) {
			obj->intMyType = 4;
		}
	}
	void Runhyd(TwowayStruct* obj) {
		double KA1;
		double KA2;
		double KB1;
		double KB2;
		double MyCurP;

		MyCurP = (obj->Ports[1].en_pressure + obj->Ports[2].en_pressure) / 2.0;

		switch (obj->intMyType) {
		case 1:
			KA1 = obj->clsPipe2->fkaMid;
			KB2 = obj->joinPipe1->fkbMid;
			KB1 = obj->TwoWayType1KB1(KA1, KB2, obj->joinPipe1->Area(obj->clsPipe2), obj->joinPipe1->roughness, obj->clsPipe2->Area(obj->joinPipe1), obj->clsPipe2->roughness);
			KA2 = 1.0 * (sqrt(KA1 + KB1) - KB2);
			obj->joinPipe1->port2VKB = sqrt(KB1);
			obj->clsPipe2->port1VKA = sqrt(KA2);
			break;
		case 2:
			KB1 = obj->clsPipe2->fkbMid;
			KA2 = obj->joinPipe1->fkaMid;
			KA1 = obj->TwoWayType2KA1(KB1, KA2, obj->joinPipe1->Area(obj->clsPipe2), obj->joinPipe1->roughness, obj->clsPipe2->Area(obj->joinPipe1), obj->clsPipe2->roughness);
			KB2 = 1.0 * sqrt(KA1 + KB1) - KA2;
			obj->joinPipe1->port1VKA = sqrt(KA1);
			obj->clsPipe2->port2VKB = sqrt(KB2);
			break;
		case 3:
			KA1 = obj->clsPipe2->fkaMid;
			KA2 = obj->joinPipe1->fkaMid;
			KB1 = obj->TwoWayType3KB1(KA1, KA2, obj->joinPipe1->Area(obj->clsPipe2), obj->joinPipe1->roughness, obj->clsPipe2->Area(obj->joinPipe1), obj->clsPipe2->roughness);
			KB2 = 1.0 * sqrt(KA1 + KB1) - KA2;
			obj->joinPipe1->port2VKB = sqrt(KB1);
			obj->clsPipe2->port2VKB = sqrt(KB2);
			break;
		case 4:
			KB1 = obj->clsPipe2->fkbMid;
			KB2 = obj->joinPipe1->fkbMid;
			KA1 = obj->TwoWayType4KA1(KB1, KB2, obj->joinPipe1->Area(obj->clsPipe2), obj->joinPipe1->roughness, obj->clsPipe2->Area(obj->joinPipe1), obj->clsPipe2->roughness);
			KA2 = 1.0 * sqrt(KA1 + KB1) - KB2;
			obj->joinPipe1->port1VKA = sqrt(KA1);
			obj->clsPipe2->port1VKA = sqrt(KA2);
			break;
		}
		obj->dblErrP = MyCurP - obj->Ports[2].en_pressure;
	}
	void DoHydraulicBack(TwowayStruct*) {

	}
	double DoKA(double, double, double, double, double, double, double, double) {


		return 0;
	}
	double DoKB(double, double, double, double, double, double, double, double) {


		return 0;
	}
	void SwapVal(TwowayStruct* obj) {
		if (obj->joinPipe1->Ports[1].JoinCode == obj->intNum) {
			obj->Ports[1].en_pressure = obj->joinPipe1->Ports[2].en_pressure;
			obj->Ports[1].en_quality = obj->joinPipe1->Ports[2].en_quality;
			obj->Ports[1].en_velocity = obj->joinPipe1->uMid;
		}
		else {
			obj->Ports[2].en_pressure = obj->joinPipe1->Ports[2].en_pressure;
			obj->Ports[2].en_quality = -1.0 * obj->joinPipe1->Ports[2].en_quality;
			obj->Ports[2].en_velocity = -1.0 * obj->joinPipe1->uMid;
		}

		if (obj->clsPipe2->Ports[1].JoinCode == obj->intNum) {
			obj->Ports[2].en_pressure = obj->clsPipe2->Ports[2].en_pressure;
			obj->Ports[2].en_quality = obj->clsPipe2->Ports[2].en_quality;
			obj->Ports[2].en_velocity = obj->clsPipe2->uMid;
		}
		else {
			obj->Ports[1].en_pressure = obj->clsPipe2->Ports[2].en_pressure;
			obj->Ports[1].en_quality = -1.0 * obj->clsPipe2->Ports[2].en_quality;
			obj->Ports[1].en_velocity = -1.0 * obj->clsPipe2->uMid;
		}

	}
	void RunThermal(TwowayStruct*) {

	}
	void TestConnection(TwowayStruct*) {

	}
	void TestTopology(TwowayStruct*) {

	}



};

struct TeeStruct {
	struct PipePort {
		double Dn;
		int JoinCode;
		int ConnectPortNo;
		double en_pressure;
		double en_velocity;
		double en_temperature;
		double en_quality;
		double dblV;
	};
	char* strName;
	int intNum;
	int intMyType;
	PipePort Ports[4];
	PipeStruct* joinPipe1;
	PipeStruct* clsPipe2;
	PipeStruct* clsPipe3;
	double dblTmix;
	double dblErrP;
	char blnConnected;//y  or   c
	int TubeNum;
	int TubeType;

	void New1(TeeStruct*) {

	}

	void New2(TeeStruct* object, int intTheTeeNum, char* strTheTeeName, int intTheTeeConnPiece1, int intTheTeeConnPort1,
		int intTheTeeConnPiece2, int intTheTeeConnPort2, int intTheTeeConnPiece3, int intTheTeeConnPort3) {

		object->intNum = intTheTeeNum;

		object->Ports[1].JoinCode = intTheTeeConnPiece1;
		object->Ports[1].ConnectPortNo = intTheTeeConnPort1;
		object->Ports[1].Dn = 1.0;
		object->Ports[2].JoinCode = intTheTeeConnPiece2;
		object->Ports[2].ConnectPortNo = intTheTeeConnPort2;
		object->Ports[2].Dn = 1.0;
		object->Ports[3].JoinCode = intTheTeeConnPiece3;
		object->Ports[3].ConnectPortNo = intTheTeeConnPort3;
		object->Ports[3].Dn = 1.0;
		object->TubeNum = intTheTeeNum;
		object->TubeType = Tee;


	}

	void Init(TeeStruct* obj, PipeStruct* pipe1, PipeStruct* pipe2, PipeStruct* pipe3) {
		obj->joinPipe1 = pipe1;
		obj->clsPipe2 = pipe2;
		obj->clsPipe3 = pipe3;
		obj->CheckTeeType(obj);
		obj->Ports[1].Dn = pipe1->diam;
		obj->Ports[2].Dn = pipe2->diam;
		obj->Ports[3].Dn = pipe3->diam;

		if (obj->Ports[1].ConnectPortNo == 1) {
			obj->Ports[1].en_temperature = pipe1->Ports[1].en_temperature;
		}
		else {
			obj->Ports[1].en_temperature = pipe1->Ports[2].en_temperature;
		}

		if (obj->Ports[2].ConnectPortNo == 1) {
			obj->Ports[2].en_temperature = pipe2->Ports[1].en_temperature;
		}
		else {
			obj->Ports[2].en_temperature = pipe2->Ports[2].en_temperature;
		}

		if (obj->Ports[3].ConnectPortNo == 1) {
			obj->Ports[3].en_temperature = pipe3->Ports[1].en_temperature;
		}
		else {
			obj->Ports[3].en_temperature = pipe3->Ports[2].en_temperature;
		}

		switch (obj->intMyType) {
		case 1:
			obj->Ports[1].en_pressure = pipe1->Ports[2].en_pressure;
			obj->Ports[1].en_velocity = pipe1->Ports[2].en_velocity;
			obj->Ports[1].en_temperature = pipe1->Ports[2].en_temperature;
			obj->Ports[2].en_pressure = pipe2->Ports[1].en_pressure;
			obj->Ports[2].en_velocity = pipe2->Ports[1].en_velocity;
			obj->Ports[2].en_temperature = pipe2->Ports[1].en_temperature;
			obj->Ports[3].en_pressure = pipe3->Ports[1].en_pressure;
			obj->Ports[3].en_velocity = pipe3->Ports[1].en_velocity;
			obj->Ports[3].en_temperature = pipe3->Ports[1].en_temperature;
			break;
		case 2:
			obj->Ports[1].en_pressure = pipe1->Ports[2].en_pressure;
			obj->Ports[1].en_velocity = pipe1->Ports[2].en_velocity;
			obj->Ports[1].en_temperature = pipe1->Ports[2].en_temperature;
			obj->Ports[2].en_pressure = pipe2->Ports[2].en_pressure;
			obj->Ports[2].en_velocity = pipe2->Ports[2].en_velocity;
			obj->Ports[2].en_temperature = pipe2->Ports[2].en_temperature;
			obj->Ports[3].en_pressure = pipe3->Ports[1].en_pressure;
			obj->Ports[3].en_velocity = pipe3->Ports[1].en_velocity;
			obj->Ports[3].en_temperature = pipe3->Ports[1].en_temperature;
			break;
		case 3:
			obj->Ports[1].en_pressure = pipe1->Ports[2].en_pressure;
			obj->Ports[1].en_velocity = pipe1->Ports[2].en_velocity;
			obj->Ports[1].en_temperature = pipe1->Ports[2].en_temperature;
			obj->Ports[2].en_pressure = pipe2->Ports[1].en_pressure;
			obj->Ports[2].en_velocity = pipe2->Ports[1].en_velocity;
			obj->Ports[2].en_temperature = pipe2->Ports[1].en_temperature;
			obj->Ports[3].en_pressure = pipe3->Ports[2].en_pressure;
			obj->Ports[3].en_velocity = pipe3->Ports[2].en_velocity;
			obj->Ports[3].en_temperature = pipe3->Ports[2].en_temperature;
			break;
		case 4:
			obj->Ports[1].en_pressure = pipe1->Ports[1].en_pressure;
			obj->Ports[1].en_velocity = pipe1->Ports[1].en_velocity;
			obj->Ports[1].en_temperature = pipe1->Ports[1].en_temperature;
			obj->Ports[2].en_pressure = pipe2->Ports[1].en_pressure;
			obj->Ports[2].en_velocity = pipe2->Ports[1].en_velocity;
			obj->Ports[2].en_temperature = pipe2->Ports[1].en_temperature;
			obj->Ports[3].en_pressure = pipe3->Ports[2].en_pressure;
			obj->Ports[3].en_velocity = pipe3->Ports[2].en_velocity;
			obj->Ports[3].en_temperature = pipe3->Ports[2].en_temperature;
			break;
		case 5:
			obj->Ports[1].en_pressure = pipe1->Ports[1].en_pressure;
			obj->Ports[1].en_velocity = pipe1->Ports[1].en_velocity;
			obj->Ports[1].en_temperature = pipe1->Ports[1].en_temperature;
			obj->Ports[2].en_pressure = pipe2->Ports[2].en_pressure;
			obj->Ports[2].en_velocity = pipe2->Ports[2].en_velocity;
			obj->Ports[2].en_temperature = pipe2->Ports[2].en_temperature;
			obj->Ports[3].en_pressure = pipe3->Ports[1].en_pressure;
			obj->Ports[3].en_velocity = pipe3->Ports[1].en_velocity;
			obj->Ports[3].en_temperature = pipe3->Ports[1].en_temperature;
			break;
		case 6:
			obj->Ports[1].en_pressure = pipe1->Ports[1].en_pressure;
			obj->Ports[1].en_velocity = pipe1->Ports[1].en_velocity;
			obj->Ports[1].en_temperature = pipe1->Ports[1].en_temperature;
			obj->Ports[2].en_pressure = pipe2->Ports[2].en_pressure;
			obj->Ports[2].en_velocity = pipe2->Ports[2].en_velocity;
			obj->Ports[2].en_temperature = pipe2->Ports[2].en_temperature;
			obj->Ports[3].en_pressure = pipe3->Ports[2].en_pressure;
			obj->Ports[3].en_velocity = pipe3->Ports[2].en_velocity;
			obj->Ports[3].en_temperature = pipe3->Ports[2].en_temperature;
			break;
		}



	}
	void CheckTeeType(TeeStruct* obj) {
		if (obj->Ports[1].ConnectPortNo == 2 && obj->Ports[2].ConnectPortNo == 1 && obj->Ports[3].ConnectPortNo == 1) {
			obj->intMyType = 1;
		}
		else if (obj->Ports[1].ConnectPortNo == 2 && obj->Ports[2].ConnectPortNo == 2 && obj->Ports[3].ConnectPortNo == 1) {
			obj->intMyType = 2;
		}
		else if (obj->Ports[1].ConnectPortNo == 2 && obj->Ports[2].ConnectPortNo == 1 && obj->Ports[3].ConnectPortNo == 2) {
			obj->intMyType = 3;
		}
		else if (obj->Ports[1].ConnectPortNo == 1 && obj->Ports[2].ConnectPortNo == 1 && obj->Ports[3].ConnectPortNo == 2) {
			obj->intMyType = 4;
		}
		else if (obj->Ports[1].ConnectPortNo == 1 && obj->Ports[2].ConnectPortNo == 2 && obj->Ports[3].ConnectPortNo == 1) {
			obj->intMyType = 5;
		}
		else if (obj->Ports[1].ConnectPortNo == 1 && obj->Ports[2].ConnectPortNo == 2 && obj->Ports[3].ConnectPortNo == 2) {
			obj->intMyType = 6;
		}
		else if (obj->Ports[1].ConnectPortNo == 1 && obj->Ports[2].ConnectPortNo == 1 && obj->Ports[3].ConnectPortNo == 1) {
			obj->intMyType = 7;
		}
		else if (obj->Ports[1].ConnectPortNo == 2 && obj->Ports[2].ConnectPortNo == 2 && obj->Ports[3].ConnectPortNo == 2) {
			obj->intMyType = 8;
		}
	}

	double TeeType1KB1(double dblKA1, double dblKB2, double dblKB3, double dblA1, double dblAS1, double dblA2, double dblAS2, double dblA3, double dblAS3) {
		double dblKB1;
		double fengzi;
		double fengmu;
		fengzi = dblKA1 * (dblA1 / dblAS1 - dblA2 / dblAS2) + 2 * (dblA2 / dblAS2 + dblKB3 * dblA3 / dblAS3);
		fengmu = dblA1 / dblAS1 + dblA2 / dblAS2;
		dblKB1 = fengzi / fengmu;
		return dblKB1;
	}

	double TeeType2KB1(double dblKA1, double dblKA2, double dblKB3, double dblA1, double dblAS1, double dblA2, double dblAS2, double dblA3, double dblAS3) {
		double dblKB1;
		dblKB1 = 1.0 * (dblKA1 * (dblA1 / dblAS1 - dblA2 / dblAS2) + 2 * (dblA2 / dblAS2 + dblKB3 * dblA3 / dblAS3)) / (dblA1 / dblAS1 + dblA2 / dblAS2 + dblA3 / dblAS3);
		return dblKB1;
	}
	double TeeType3KB1(double dblKA1, double dblKB2, double dblKA3, double dblA1, double dblAS1, double dblA2, double dblAS2, double dblA3, double dblAS3) {
		double dblKB1;

		dblKB1 = 1.0 * (dblKA1 * (dblA1 / dblAS1 - dblA2 / dblAS2) + 2 * (dblA2 / dblAS2 + dblKA3 * dblA3 / dblAS3)) / (dblA1 / dblAS1 + dblA2 / dblAS2 + dblA3 / dblAS3);

		return dblKB1;
	}

	double TeeType4KB3(double dblKB1, double dblKB2, double dblKA3, double dblA1, double dblAS1, double dblA2, double dblAS2, double dblA3, double dblAS3) {
		double dblKB3;

		dblKB3 = 1.0 * (dblKA3 * (dblA3 / dblAS3 - dblA1 / dblAS1) + 2 * (dblKB1 / dblAS1 + dblKB2 * dblA2 / dblAS2)) / (dblA1 / dblAS1 + dblA2 / dblAS2 + dblA3 / dblAS3);

		return dblKB3;


	}
	double TeeType5KB2(double dblKB1, double dblKA2, double dblKB3, double dblA1, double dblAS1, double dblA2, double dblAS2, double dblA3, double dblAS3) {

		double dblKB2;

		dblKB2 = 1.0 * (dblKA2 * (dblA2 / dblAS2 - dblA1 / dblAS1) + 2 * (dblKB1 / dblAS1 + dblKB3 * dblA3 / dblAS3)) / (dblA1 / dblAS1 + dblA2 / dblAS2 + dblA3 / dblAS3);

		return dblKB2;
	}
	double TeeType6KB2(double dblKB1, double dblKA2, double dblKA3, double dblA1, double dblAS1, double dblA2, double dblAS2, double dblA3, double dblAS3) {
		double dblKB2;

		dblKB2 = 1.0 * (dblKA2 * (dblA2 / dblAS2 - dblA1 / dblAS1) + 2 * (dblKB1 / dblAS1 + dblKA3 * dblA3 / dblAS3)) / (dblA1 / dblAS1 + dblA2 / dblAS2 + dblA3 / dblAS3);

		return dblKB2;
	}
	double TeeType7KA1(double dblKB1, double dblKB2, double dblKB3, double dblA1, double dblAS1, double dblA2, double dblAS2, double dblA3, double dblAS3) {
		double dblKA1;
		double fengzi;
		double fengmu;
		fengzi = 1.0 * dblKB1 * (dblA1 / dblAS1 - dblA2 / dblAS2) + 2 * (dblKB2 / dblAS2 + dblKB3 * dblA3 / dblAS3);
		fengmu = 1.0 * dblA1 / dblAS1 + dblA2 / dblAS2;
		dblKA1 = fengzi / fengmu;
		return dblKA1;

	}
	double TeeType8KB1(double dblKA1, double dblKA2, double dblKA3, double dblA1, double dblAS1, double dblA2, double dblAS2, double dblA3, double dblAS3) {
		double dblKB1;
		double fengzi;
		double fengmu;
		fengzi = 1.0 * dblKA1 * (dblA1 / dblAS1 - dblA2 / dblAS2) + 2 * (dblKA2 / dblAS2 + dblKA3 * dblA3 / dblAS3);
		fengmu = 1.0 * dblA1 / dblAS1 + dblA2 / dblAS2;
		dblKB1 = fengzi / fengmu;
		return dblKB1;

	}


	void Runhyd(TeeStruct* obj) {
		double KA1;
		double KA2;
		double KA3;
		double KB1;
		double KB2;
		double KB3;
		double MyCurP;
		MyCurP = (obj->Ports[1].en_pressure + obj->Ports[2].en_pressure + obj->Ports[2].en_pressure) / 3.0;

		switch (obj->intMyType) {
		case 1:
			KA1 = obj->clsPipe2->fkaMid;
			KB2 = obj->clsPipe3->fkbMid;
			KB3 = obj->joinPipe1->fkbMid;
			KB1 = obj->TeeType1KB1(KA1, KB2, KB3, obj->joinPipe1->Area(obj->clsPipe2), obj->joinPipe1->roughness, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->roughness, obj->clsPipe3->Area(obj->joinPipe1), obj->clsPipe3->roughness);
			KA2 = 1.0 * (sqrt(KA1 + KB1) - KB2);
			KA3 = 1.0 * (sqrt(KA1 + KB1) - KB3);
			obj->joinPipe1->port2VKB = sqrt(KB1);
			obj->clsPipe2->port1VKA = sqrt(KA2);
			obj->clsPipe3->port1VKA = sqrt(KA3);
			break;
		case 2:
			KA1 = obj->clsPipe2->fkaMid;
			KA2 = obj->clsPipe3->fkaMid;
			KB3 = obj->joinPipe1->fkbMid;
			KB1 = obj->TeeType2KB1(KA1, KA2, KB3, obj->joinPipe1->Area(obj->clsPipe2), obj->joinPipe1->roughness, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->roughness, obj->clsPipe3->Area(obj->joinPipe1), obj->clsPipe3->roughness);
			KB2 = 1.0 * (sqrt(KA1 + KB1) - KA2);
			KA3 = 1.0 * (sqrt(KA1 + KB1) - KB3);
			obj->joinPipe1->port2VKB = sqrt(KB1);
			obj->clsPipe2->port2VKB = sqrt(KB2);
			obj->clsPipe3->port1VKA = sqrt(KA3);
			break;
		case 3:
			KA1 = obj->clsPipe2->fkaMid;
			KB2 = obj->clsPipe3->fkbMid;
			KA3 = obj->joinPipe1->fkaMid;
			KB1 = obj->TeeType3KB1(KA1, KB2, KA3, obj->joinPipe1->Area(obj->clsPipe2), obj->joinPipe1->roughness, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->roughness, obj->clsPipe3->Area(obj->joinPipe1), obj->clsPipe3->roughness);
			KA2 = 1.0 * (sqrt(KA1 + KB1) - KB2);
			KB3 = 1.0 * (sqrt(KA1 + KB1) - KA3);
			obj->joinPipe1->port2VKB = sqrt(KB1);
			obj->clsPipe2->port1VKA = sqrt(KA2);
			obj->clsPipe3->port2VKB = sqrt(KB3);
			break;

		case 4:
			KB1 = obj->clsPipe2->fkbMid;
			KB2 = obj->clsPipe3->fkbMid;
			KA3 = obj->joinPipe1->fkaMid;
			KB3 = obj->TeeType4KB3(KB1, KB2, KA3, obj->joinPipe1->Area(obj->clsPipe2), obj->joinPipe1->roughness, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->roughness, obj->clsPipe3->Area(obj->joinPipe1), obj->clsPipe3->roughness);
			KA1 = 1.0 * (sqrt(KA3 + KB3) - KB1);
			KA2 = 1.0 * (sqrt(KA3 + KB3) - KB2);
			obj->joinPipe1->port1VKA = sqrt(KA1);
			obj->clsPipe2->port1VKA = sqrt(KA2);
			obj->clsPipe3->port2VKB = sqrt(KB3);
			break;

		case 5:
			KB1 = obj->clsPipe2->fkbMid;
			KA2 = obj->clsPipe3->fkaMid;
			KB3 = obj->joinPipe1->fkbMid;
			KB2 = obj->TeeType5KB2(KB1, KA2, KB3, obj->joinPipe1->Area(obj->clsPipe2), obj->joinPipe1->roughness, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->roughness, obj->clsPipe3->Area(obj->joinPipe1), obj->clsPipe3->roughness);
			KA1 = 1.0 * sqrt(KA2 + KB2) - KB1;
			KA3 = 1.0 * sqrt(KA2 + KB2) - KB3;
			obj->joinPipe1->port1VKA = sqrt(KA1);
			obj->clsPipe2->port2VKB = sqrt(KB2);
			obj->clsPipe3->port1VKA = sqrt(KA3);
			break;
		case 6:
			KB1 = obj->clsPipe2->fkbMid;
			KA2 = obj->clsPipe3->fkaMid;
			KA3 = obj->joinPipe1->fkaMid;
			KB2 = obj->TeeType6KB2(KB1, KA2, KA3, obj->joinPipe1->Area(obj->clsPipe2), obj->joinPipe1->roughness, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->roughness, obj->clsPipe3->Area(obj->joinPipe1), obj->clsPipe3->roughness);
			KA1 = 1.0 * sqrt(KA2 + KB2) - KB1;
			KB3 = 1.0 * sqrt(KA2 + KB2) - KA3;
			obj->joinPipe1->port1VKA = sqrt(KA1);
			obj->clsPipe2->port2VKB = sqrt(KB2);
			obj->clsPipe3->port2VKB = sqrt(KB3);
			break;

		case 7:
			KB1 = obj->clsPipe2->fkbMid;
			KB2 = obj->clsPipe3->fkbMid;
			KB3 = obj->joinPipe1->fkbMid;
			KA1 = obj->TeeType7KA1(KB1, KB2, KB3, obj->joinPipe1->Area(obj->clsPipe2), obj->joinPipe1->roughness, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->roughness, obj->clsPipe3->Area(obj->joinPipe1), obj->clsPipe3->roughness);
			KA2 = 1.0 * sqrt(KA1 + KB1) - KB2;
			KA3 = 1.0 * sqrt(KA1 + KB1) - KB3;
			obj->joinPipe1->port1VKA = sqrt(KA1);
			obj->clsPipe2->port1VKA = sqrt(KA2);
			obj->clsPipe3->port1VKA = sqrt(KA3);
			break;
		case 8:
			KA1 = obj->clsPipe2->fkaMid;
			KA2 = obj->clsPipe3->fkaMid;
			KA3 = obj->joinPipe1->fkaMid;
			KB1 = obj->TeeType8KB1(KA1, KA2, KA3, obj->joinPipe1->Area(obj->clsPipe2), obj->joinPipe1->roughness, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->roughness, obj->clsPipe3->Area(obj->joinPipe1), obj->clsPipe3->roughness);
			KB2 = 1.0 * sqrt(KA1 + KB1) - KA2;
			KB3 = 1.0 * sqrt(KA1 + KB1) - KA3;
			obj->joinPipe1->port2VKB = sqrt(KB1);
			obj->clsPipe2->port2VKB = sqrt(KB2);
			obj->clsPipe3->port2VKB = sqrt(KB3);
			break;
		}
		obj->dblErrP = MyCurP - obj->Ports[3].en_pressure;

	}
	void DoHydraulicBack(TeeStruct*) {

	}


	double DoKA(double, double, double, double, double, double, double, double) {


		return 0;
	}
	double DoKB(double, double, double, double, double, double, double, double) {


		return 0;
	}
	void SwapVal(TeeStruct* obj) {

		if (obj->joinPipe1->Ports[1].JoinCode == obj->intNum) {
			obj->Ports[1].en_pressure = obj->joinPipe1->Ports[2].en_pressure;
			obj->Ports[1].en_quality = obj->joinPipe1->Ports[2].en_quality;
			obj->Ports[1].en_velocity = obj->joinPipe1->uMid;

		}
		else {
			obj->Ports[2].en_pressure = obj->joinPipe1->Ports[2].en_pressure;
			obj->Ports[2].en_quality = -1.0 * obj->joinPipe1->Ports[2].en_quality;
			obj->Ports[2].en_velocity = -1.0 * obj->joinPipe1->uMid;

		}

		if (obj->clsPipe2->Ports[1].JoinCode == obj->intNum) {
			obj->Ports[2].en_pressure = obj->clsPipe2->Ports[2].en_pressure;
			obj->Ports[2].en_quality = obj->clsPipe2->Ports[2].en_quality;
			obj->Ports[2].en_velocity = obj->clsPipe2->uMid;

		}
		else {
			obj->Ports[2].en_pressure = obj->clsPipe2->Ports[1].en_pressure;
			obj->Ports[2].en_quality = -1.0 * obj->clsPipe2->Ports[1].en_quality;
			obj->Ports[2].en_velocity = -1.0 * obj->clsPipe2->uMid;

		}

		if (obj->clsPipe3->Ports[1].JoinCode == obj->intNum) {
			obj->Ports[3].en_pressure = obj->clsPipe3->Ports[2].en_pressure;
			obj->Ports[3].en_quality = obj->clsPipe3->Ports[2].en_quality;
			obj->Ports[3].en_velocity = obj->clsPipe3->uMid;

		}
		else {
			obj->Ports[3].en_pressure = obj->clsPipe3->Ports[1].en_pressure;
			obj->Ports[3].en_quality = -1.0 * obj->clsPipe3->Ports[1].en_quality;
			obj->Ports[3].en_velocity = -1.0 * obj->clsPipe3->uMid;

		}
	}
	void RunThermal(TeeStruct*) {

	}
	void TestConnection(TeeStruct*) {

	}
	void TestTopology(TeeStruct*) {

	}


};

struct CrossStruct {
	struct PipePort {
		double Dn;
		int JoinCode;
		int ConnectPortNo;
		double en_pressure;
		double en_velocity;
		double en_temperature;
		double en_quality;
		double dblV;
	};

	char* strName;
	int intNum;
	int intType;
	PipePort Ports[5];
	PipeStruct* joinPipe1;
	PipeStruct* clsPipe2;
	PipeStruct* clsPipe3;
	PipeStruct* clsPipe4;
	double dblTmix;
	double dblErrP;
	char blnConnected;//y  or   c
	int TubeNum;
	int TubeType;


	void New1(CrossStruct*) {

	}

	void New2(CrossStruct* object, int intTheCrossNum, char* strTheCrossName, int intTheCrossConnPiece1,
		int intTheCrossConnPort1, int intTheCrossConnPiece2, int intTheCrossConnPort2,
		int intTheCrossConnPiece3, int intTheCrossConnPort3, int intTheCrossConnPiece4, int intTheCrossConnPort4) {

		object->intNum = intTheCrossNum;

		object->Ports[1].JoinCode = intTheCrossConnPiece1;
		object->Ports[1].ConnectPortNo = intTheCrossConnPort1;
		object->Ports[1].Dn = 1.0;
		object->Ports[2].JoinCode = intTheCrossConnPiece2;
		object->Ports[2].ConnectPortNo = intTheCrossConnPort2;
		object->Ports[2].Dn = 1.0;
		object->Ports[3].JoinCode = intTheCrossConnPiece3;
		object->Ports[3].ConnectPortNo = intTheCrossConnPort3;
		object->Ports[3].Dn = 1.0;
		object->Ports[4].JoinCode = intTheCrossConnPiece4;
		object->Ports[4].ConnectPortNo = intTheCrossConnPort4;
		object->Ports[4].Dn = 1.0;
		object->TubeNum = intTheCrossNum;
		object->TubeType = Cross;




	}

	void Init(CrossStruct* obj, PipeStruct* pipe1, PipeStruct* pipe2, PipeStruct* pipe3, PipeStruct* pipe4) {
		obj->joinPipe1 = pipe1;
		obj->clsPipe2 = pipe2;
		obj->clsPipe3 = pipe3;
		obj->clsPipe4 = pipe4;
		obj->CheckCrossType(obj);
		obj->Ports[1].Dn = pipe1->diam;
		obj->Ports[2].Dn = pipe2->diam;
		obj->Ports[3].Dn = pipe3->diam;
		obj->Ports[4].Dn = pipe4->diam;


		switch (obj->intType) {
		case 1:
			obj->Ports[1].en_pressure = pipe1->Ports[2].en_pressure;
			obj->Ports[1].en_velocity = pipe1->Ports[2].en_velocity;
			obj->Ports[1].en_temperature = pipe1->Ports[2].en_temperature;
			obj->Ports[2].en_pressure = pipe2->Ports[2].en_pressure;
			obj->Ports[2].en_velocity = pipe2->Ports[2].en_velocity;
			obj->Ports[2].en_temperature = pipe2->Ports[2].en_temperature;
			obj->Ports[3].en_pressure = pipe3->Ports[2].en_pressure;
			obj->Ports[3].en_velocity = pipe3->Ports[2].en_velocity;
			obj->Ports[3].en_temperature = pipe3->Ports[2].en_temperature;
			obj->Ports[4].en_pressure = pipe4->Ports[1].en_pressure;
			obj->Ports[4].en_velocity = pipe4->Ports[1].en_velocity;
			obj->Ports[4].en_temperature = pipe4->Ports[1].en_temperature;
			break;
		case 2:
			obj->Ports[1].en_pressure = pipe1->Ports[2].en_pressure;
			obj->Ports[1].en_velocity = pipe1->Ports[2].en_velocity;
			obj->Ports[1].en_temperature = pipe1->Ports[2].en_temperature;
			obj->Ports[2].en_pressure = pipe2->Ports[2].en_pressure;
			obj->Ports[2].en_velocity = pipe2->Ports[2].en_velocity;
			obj->Ports[2].en_temperature = pipe2->Ports[2].en_temperature;
			obj->Ports[3].en_pressure = pipe3->Ports[1].en_pressure;
			obj->Ports[3].en_velocity = pipe3->Ports[1].en_velocity;
			obj->Ports[3].en_temperature = pipe3->Ports[1].en_temperature;
			obj->Ports[4].en_pressure = pipe4->Ports[2].en_pressure;
			obj->Ports[4].en_velocity = pipe4->Ports[2].en_velocity;
			obj->Ports[4].en_temperature = pipe4->Ports[2].en_temperature;
			break;
		case 3:
			obj->Ports[1].en_pressure = pipe1->Ports[2].en_pressure;
			obj->Ports[1].en_velocity = pipe1->Ports[2].en_velocity;
			obj->Ports[1].en_temperature = pipe1->Ports[2].en_temperature;
			obj->Ports[2].en_pressure = pipe2->Ports[2].en_pressure;
			obj->Ports[2].en_velocity = pipe2->Ports[2].en_velocity;
			obj->Ports[2].en_temperature = pipe2->Ports[2].en_temperature;
			obj->Ports[3].en_pressure = pipe3->Ports[1].en_pressure;
			obj->Ports[3].en_velocity = pipe3->Ports[1].en_velocity;
			obj->Ports[3].en_temperature = pipe3->Ports[1].en_temperature;
			obj->Ports[4].en_pressure = pipe4->Ports[1].en_pressure;
			obj->Ports[4].en_velocity = pipe4->Ports[1].en_velocity;
			obj->Ports[4].en_temperature = pipe4->Ports[1].en_temperature;
			break;
		case 4:
			obj->Ports[1].en_pressure = pipe1->Ports[2].en_pressure;
			obj->Ports[1].en_velocity = pipe1->Ports[2].en_velocity;
			obj->Ports[1].en_temperature = pipe1->Ports[2].en_temperature;
			obj->Ports[2].en_pressure = pipe2->Ports[1].en_pressure;
			obj->Ports[2].en_velocity = pipe2->Ports[1].en_velocity;
			obj->Ports[2].en_temperature = pipe2->Ports[1].en_temperature;
			obj->Ports[3].en_pressure = pipe3->Ports[2].en_pressure;
			obj->Ports[3].en_velocity = pipe3->Ports[2].en_velocity;
			obj->Ports[3].en_temperature = pipe3->Ports[2].en_temperature;
			obj->Ports[4].en_pressure = pipe4->Ports[2].en_pressure;
			obj->Ports[4].en_velocity = pipe4->Ports[2].en_velocity;
			obj->Ports[4].en_temperature = pipe4->Ports[2].en_temperature;
			break;
		case 5:
			obj->Ports[1].en_pressure = pipe1->Ports[2].en_pressure;
			obj->Ports[1].en_velocity = pipe1->Ports[2].en_velocity;
			obj->Ports[1].en_temperature = pipe1->Ports[2].en_temperature;
			obj->Ports[2].en_pressure = pipe2->Ports[1].en_pressure;
			obj->Ports[2].en_velocity = pipe2->Ports[1].en_velocity;
			obj->Ports[2].en_temperature = pipe2->Ports[1].en_temperature;
			obj->Ports[3].en_pressure = pipe3->Ports[2].en_pressure;
			obj->Ports[3].en_velocity = pipe3->Ports[2].en_velocity;
			obj->Ports[3].en_temperature = pipe3->Ports[2].en_temperature;
			obj->Ports[4].en_pressure = pipe4->Ports[1].en_pressure;
			obj->Ports[4].en_velocity = pipe4->Ports[1].en_velocity;
			obj->Ports[4].en_temperature = pipe4->Ports[1].en_temperature;
			break;
		case 6:
			obj->Ports[1].en_pressure = pipe1->Ports[2].en_pressure;
			obj->Ports[1].en_velocity = pipe1->Ports[2].en_velocity;
			obj->Ports[1].en_temperature = pipe1->Ports[2].en_temperature;
			obj->Ports[2].en_pressure = pipe2->Ports[1].en_pressure;
			obj->Ports[2].en_velocity = pipe2->Ports[1].en_velocity;
			obj->Ports[2].en_temperature = pipe2->Ports[1].en_temperature;
			obj->Ports[3].en_pressure = pipe3->Ports[1].en_pressure;
			obj->Ports[3].en_velocity = pipe3->Ports[1].en_velocity;
			obj->Ports[3].en_temperature = pipe3->Ports[1].en_temperature;
			obj->Ports[4].en_pressure = pipe4->Ports[2].en_pressure;
			obj->Ports[4].en_velocity = pipe4->Ports[2].en_velocity;
			obj->Ports[4].en_temperature = pipe4->Ports[2].en_temperature;
			break;
		case 7:
			obj->Ports[1].en_pressure = pipe1->Ports[2].en_pressure;
			obj->Ports[1].en_velocity = pipe1->Ports[2].en_velocity;
			obj->Ports[1].en_temperature = pipe1->Ports[2].en_temperature;
			obj->Ports[2].en_pressure = pipe2->Ports[1].en_pressure;
			obj->Ports[2].en_velocity = pipe2->Ports[1].en_velocity;
			obj->Ports[2].en_temperature = pipe2->Ports[1].en_temperature;
			obj->Ports[3].en_pressure = pipe3->Ports[1].en_pressure;
			obj->Ports[3].en_velocity = pipe3->Ports[1].en_velocity;
			obj->Ports[3].en_temperature = pipe3->Ports[1].en_temperature;
			obj->Ports[4].en_pressure = pipe4->Ports[1].en_pressure;
			obj->Ports[4].en_velocity = pipe4->Ports[1].en_velocity;
			obj->Ports[4].en_temperature = pipe4->Ports[1].en_temperature;
			break;
		case 8:
			obj->Ports[1].en_pressure = pipe1->Ports[1].en_pressure;
			obj->Ports[1].en_velocity = pipe1->Ports[1].en_velocity;
			obj->Ports[1].en_temperature = pipe1->Ports[1].en_temperature;
			obj->Ports[2].en_pressure = pipe2->Ports[2].en_pressure;
			obj->Ports[2].en_velocity = pipe2->Ports[2].en_velocity;
			obj->Ports[2].en_temperature = pipe2->Ports[2].en_temperature;
			obj->Ports[3].en_pressure = pipe3->Ports[2].en_pressure;
			obj->Ports[3].en_velocity = pipe3->Ports[2].en_velocity;
			obj->Ports[3].en_temperature = pipe3->Ports[2].en_temperature;
			obj->Ports[4].en_pressure = pipe4->Ports[2].en_pressure;
			obj->Ports[4].en_velocity = pipe4->Ports[2].en_velocity;
			obj->Ports[4].en_temperature = pipe4->Ports[2].en_temperature;
			break;
		case 9:
			obj->Ports[1].en_pressure = pipe1->Ports[1].en_pressure;
			obj->Ports[1].en_velocity = pipe1->Ports[1].en_velocity;
			obj->Ports[1].en_temperature = pipe1->Ports[1].en_temperature;
			obj->Ports[2].en_pressure = pipe2->Ports[2].en_pressure;
			obj->Ports[2].en_velocity = pipe2->Ports[2].en_velocity;
			obj->Ports[2].en_temperature = pipe2->Ports[2].en_temperature;
			obj->Ports[3].en_pressure = pipe3->Ports[2].en_pressure;
			obj->Ports[3].en_velocity = pipe3->Ports[2].en_velocity;
			obj->Ports[3].en_temperature = pipe3->Ports[2].en_temperature;
			obj->Ports[4].en_pressure = pipe4->Ports[1].en_pressure;
			obj->Ports[4].en_velocity = pipe4->Ports[1].en_velocity;
			obj->Ports[4].en_temperature = pipe4->Ports[1].en_temperature;
			break;
		case 10:
			obj->Ports[1].en_pressure = pipe1->Ports[1].en_pressure;
			obj->Ports[1].en_velocity = pipe1->Ports[1].en_velocity;
			obj->Ports[1].en_temperature = pipe1->Ports[1].en_temperature;
			obj->Ports[2].en_pressure = pipe2->Ports[2].en_pressure;
			obj->Ports[2].en_velocity = pipe2->Ports[2].en_velocity;
			obj->Ports[2].en_temperature = pipe2->Ports[2].en_temperature;
			obj->Ports[3].en_pressure = pipe3->Ports[1].en_pressure;
			obj->Ports[3].en_velocity = pipe3->Ports[1].en_velocity;
			obj->Ports[3].en_temperature = pipe3->Ports[1].en_temperature;
			obj->Ports[4].en_pressure = pipe4->Ports[2].en_pressure;
			obj->Ports[4].en_velocity = pipe4->Ports[2].en_velocity;
			obj->Ports[4].en_temperature = pipe4->Ports[2].en_temperature;
			break;
		case 11:
			obj->Ports[1].en_pressure = pipe1->Ports[1].en_pressure;
			obj->Ports[1].en_velocity = pipe1->Ports[1].en_velocity;
			obj->Ports[1].en_temperature = pipe1->Ports[1].en_temperature;
			obj->Ports[2].en_pressure = pipe2->Ports[2].en_pressure;
			obj->Ports[2].en_velocity = pipe2->Ports[2].en_velocity;
			obj->Ports[2].en_temperature = pipe2->Ports[2].en_temperature;
			obj->Ports[3].en_pressure = pipe3->Ports[1].en_pressure;
			obj->Ports[3].en_velocity = pipe3->Ports[1].en_velocity;
			obj->Ports[3].en_temperature = pipe3->Ports[1].en_temperature;
			obj->Ports[4].en_pressure = pipe4->Ports[1].en_pressure;
			obj->Ports[4].en_velocity = pipe4->Ports[1].en_velocity;
			obj->Ports[4].en_temperature = pipe4->Ports[1].en_temperature;
			break;
		case 12:
			obj->Ports[1].en_pressure = pipe1->Ports[1].en_pressure;
			obj->Ports[1].en_velocity = pipe1->Ports[1].en_velocity;
			obj->Ports[1].en_temperature = pipe1->Ports[1].en_temperature;
			obj->Ports[2].en_pressure = pipe2->Ports[1].en_pressure;
			obj->Ports[2].en_velocity = pipe2->Ports[1].en_velocity;
			obj->Ports[2].en_temperature = pipe2->Ports[1].en_temperature;
			obj->Ports[3].en_pressure = pipe3->Ports[2].en_pressure;
			obj->Ports[3].en_velocity = pipe3->Ports[2].en_velocity;
			obj->Ports[3].en_temperature = pipe3->Ports[2].en_temperature;
			obj->Ports[4].en_pressure = pipe4->Ports[2].en_pressure;
			obj->Ports[4].en_velocity = pipe4->Ports[2].en_velocity;
			obj->Ports[4].en_temperature = pipe4->Ports[2].en_temperature;
			break;
		case 13:
			obj->Ports[1].en_pressure = pipe1->Ports[1].en_pressure;
			obj->Ports[1].en_velocity = pipe1->Ports[1].en_velocity;
			obj->Ports[1].en_temperature = pipe1->Ports[1].en_temperature;
			obj->Ports[2].en_pressure = pipe2->Ports[1].en_pressure;
			obj->Ports[2].en_velocity = pipe2->Ports[1].en_velocity;
			obj->Ports[2].en_temperature = pipe2->Ports[1].en_temperature;
			obj->Ports[3].en_pressure = pipe3->Ports[2].en_pressure;
			obj->Ports[3].en_velocity = pipe3->Ports[2].en_velocity;
			obj->Ports[3].en_temperature = pipe3->Ports[2].en_temperature;
			obj->Ports[4].en_pressure = pipe4->Ports[1].en_pressure;
			obj->Ports[4].en_velocity = pipe4->Ports[1].en_velocity;
			obj->Ports[4].en_temperature = pipe4->Ports[1].en_temperature;
			break;
		case 14:
			obj->Ports[1].en_pressure = pipe1->Ports[1].en_pressure;
			obj->Ports[1].en_velocity = pipe1->Ports[1].en_velocity;
			obj->Ports[1].en_temperature = pipe1->Ports[1].en_temperature;
			obj->Ports[2].en_pressure = pipe2->Ports[1].en_pressure;
			obj->Ports[2].en_velocity = pipe2->Ports[1].en_velocity;
			obj->Ports[2].en_temperature = pipe2->Ports[1].en_temperature;
			obj->Ports[3].en_pressure = pipe3->Ports[1].en_pressure;
			obj->Ports[3].en_velocity = pipe3->Ports[1].en_velocity;
			obj->Ports[3].en_temperature = pipe3->Ports[1].en_temperature;
			obj->Ports[4].en_pressure = pipe4->Ports[2].en_pressure;
			obj->Ports[4].en_velocity = pipe4->Ports[2].en_velocity;
			obj->Ports[4].en_temperature = pipe4->Ports[2].en_temperature;
			break;
		}


	}

	void CheckCrossType(CrossStruct* obj) {
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

	void Runhyd(CrossStruct* obj) {
		double KA1;
		double KA2;
		double KA3;
		double KA4;
		double KB1;
		double KB2;
		double KB3;
		double KB4;
		double MyCurP;
		MyCurP = (obj->Ports[1].en_pressure + obj->Ports[2].en_pressure + obj->Ports[3].en_pressure + obj->Ports[4].en_pressure) / 4.0;
		switch (obj->intType) {
		case 1:
			KA1 = obj->clsPipe2->fkaMid;
			KA2 = obj->joinPipe1->fkaMid;
			KA3 = obj->clsPipe4->fkaMid;
			KA4 = obj->clsPipe3->fkaMid;
			KB1 = obj->CrossType1KB1(KA1, KA2, KA3, KA4, obj->joinPipe1->Area(obj->clsPipe2), obj->joinPipe1->roughness, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->roughness, obj->clsPipe3->Area(obj->clsPipe4), obj->clsPipe3->roughness, obj->clsPipe4->Area(obj->joinPipe1), obj->clsPipe4->roughness);
			KB2 = 1.0 * sqrt(KA1 + KA2) - KA2;
			KB3 = 1.0 * sqrt(KA1 + KB2) - KA3;
			KB4 = 1.0 * sqrt(KA1 + KB3) - KA4;


			obj->joinPipe1->port2VKB = sqrt(KB1);
			obj->clsPipe2->port2VKB = sqrt(KB2);
			obj->clsPipe3->port2VKB = sqrt(KB3);
			obj->clsPipe4->port2VKB = sqrt(KB4);

			break;
		case 2:
			KB1 = obj->clsPipe2->fkbMid;
			KA2 = obj->joinPipe1->fkaMid;
			KB3 = obj->clsPipe4->fkbMid;
			KB4 = obj->clsPipe3->fkbMid;
			KA1 = obj->CrossType2KB1(KB1, KA2, KB3, KB4, obj->joinPipe1->Area(obj->clsPipe2), obj->joinPipe1->roughness, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->roughness, obj->clsPipe3->Area(obj->clsPipe4), obj->clsPipe3->roughness, obj->clsPipe4->Area(obj->joinPipe1), obj->clsPipe4->roughness);

			KB2 = 1.0 * sqrt(KA1 + KB1) - KA2;
			KA3 = 1.0 * sqrt(KA1 + KB1) - KB3;
			KA4 = 1.0 * sqrt(KA1 + KB1) - KB4;

			obj->joinPipe1->port1VKA = sqrt(KA1);
			obj->clsPipe2->port2VKB = sqrt(KB2);
			obj->clsPipe3->port1VKA = sqrt(KA3);
			obj->clsPipe4->port1VKA = sqrt(KA4);

			break;
		case 3:
			KA1 = obj->clsPipe2->fkaMid;
			KA2 = obj->joinPipe1->fkaMid;
			KB3 = obj->clsPipe4->fkbMid;
			KB4 = obj->clsPipe3->fkbMid;
			KB1 = obj->CrossType3KB1(KA1, KA2, KB3, KB4, obj->joinPipe1->Area(obj->clsPipe2), obj->joinPipe1->roughness, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->roughness, obj->clsPipe3->Area(obj->clsPipe4), obj->clsPipe3->roughness, obj->clsPipe4->Area(obj->joinPipe1), obj->clsPipe4->roughness);
			KB2 = 1.0 * sqrt(KA1 + KB1) - KA2;
			KA3 = 1.0 * sqrt(KA1 + KB1) - KB3;
			KA4 = 1.0 * sqrt(KA1 + KB1) - KB4;
			obj->joinPipe1->port2VKB = sqrt(KB1);
			obj->clsPipe2->port2VKB = sqrt(KB2);
			obj->clsPipe3->port1VKA = sqrt(KA3);
			obj->clsPipe4->port1VKA = sqrt(KA4);

			break;

		case 4:
			KA1 = obj->clsPipe2->fkaMid;
			KB2 = obj->joinPipe1->fkbMid;
			KB3 = obj->clsPipe4->fkbMid;
			KA4 = obj->clsPipe3->fkaMid;
			KB1 = obj->CrossType4KB1(KA1, KB2, KB3, KA4, obj->joinPipe1->Area(obj->clsPipe2), obj->joinPipe1->roughness, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->roughness, obj->clsPipe3->Area(obj->clsPipe4), obj->clsPipe3->roughness, obj->clsPipe4->Area(obj->joinPipe1), obj->clsPipe4->roughness);

			KA2 = 1.0 * sqrt(KA1 + KB1) - KB2;
			KA3 = 1.0 * sqrt(KA1 + KB1) - KB3;
			KB4 = 1.0 * sqrt(KA1 + KB1) - KA4;
			obj->joinPipe1->port2VKB = sqrt(KB1);
			obj->clsPipe2->port1VKA = sqrt(KA2);
			obj->clsPipe3->port1VKA = sqrt(KA3);
			obj->clsPipe4->port2VKB = sqrt(KB4);

			break;

		case 5:
			KA1 = obj->clsPipe2->fkaMid;
			KB2 = obj->joinPipe1->fkbMid;
			KA3 = obj->clsPipe4->fkaMid;
			KB4 = obj->clsPipe3->fkbMid;
			KB1 = obj->CrossType5KB1(KA1, KB2, KA3, KB4, obj->joinPipe1->Area(obj->clsPipe2), obj->joinPipe1->roughness, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->roughness, obj->clsPipe3->Area(obj->clsPipe4), obj->clsPipe3->roughness, obj->clsPipe4->Area(obj->joinPipe1), obj->clsPipe4->roughness);

			KA2 = 1.0 * sqrt(KA1 + KB1) - KB2;
			KB3 = 1.0 * sqrt(KA1 + KB1) - KA3;
			KA4 = 1.0 * sqrt(KA1 + KB1) - KB4;
			obj->joinPipe1->port2VKB = sqrt(KB1);
			obj->clsPipe2->port1VKA = sqrt(KA2);
			obj->clsPipe3->port2VKB = sqrt(KB3);
			obj->clsPipe4->port1VKA = sqrt(KA4);

			break;

		case 6:
			KA1 = obj->clsPipe2->fkaMid;
			KB2 = obj->joinPipe1->fkbMid;
			KA3 = obj->clsPipe4->fkaMid;
			KA4 = obj->clsPipe3->fkbMid;
			KB1 = obj->CrossType6KB1(KA1, KB2, KA3, KA4, obj->joinPipe1->Area(obj->clsPipe2), obj->joinPipe1->roughness, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->roughness, obj->clsPipe3->Area(obj->clsPipe4), obj->clsPipe3->roughness, obj->clsPipe4->Area(obj->joinPipe1), obj->clsPipe4->roughness);

			KA2 = 1.0 * sqrt(KA1 + KB1) - KB2;
			KB3 = 1.0 * sqrt(KA1 + KB1) - KA3;
			KB4 = 1.0 * sqrt(KA1 + KB1) - KA4;
			obj->joinPipe1->port2VKB = sqrt(KB1);
			obj->clsPipe2->port1VKA = sqrt(KA2);
			obj->clsPipe3->port2VKB = sqrt(KB3);
			obj->clsPipe4->port2VKB = sqrt(KB4);

			break;
		case 7:
			KA1 = obj->clsPipe2->fkaMid;
			KB2 = obj->joinPipe1->fkbMid;
			KB3 = obj->clsPipe4->fkbMid;
			KB4 = obj->clsPipe3->fkbMid;
			KB1 = obj->CrossType7KB1(KA1, KB2, KB3, KB4, obj->joinPipe1->Area(obj->clsPipe2), obj->joinPipe1->roughness, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->roughness, obj->clsPipe3->Area(obj->clsPipe4), obj->clsPipe3->roughness, obj->clsPipe4->Area(obj->joinPipe1), obj->clsPipe4->roughness);

			KA2 = 1.0 * sqrt(KA1 + KB1) - KB2;
			KA3 = 1.0 * sqrt(KA1 + KB1) - KB3;
			KA4 = 1.0 * sqrt(KA1 + KB1) - KB4;
			obj->joinPipe1->port2VKB = sqrt(KB1);
			obj->clsPipe2->port1VKA = sqrt(KA2);
			obj->clsPipe3->port1VKA = sqrt(KA3);
			obj->clsPipe4->port1VKA = sqrt(KA4);

			break;

		case 8:
			KB1 = obj->clsPipe2->fkbMid;
			KA2 = obj->joinPipe1->fkaMid;
			KA3 = obj->clsPipe4->fkaMid;
			KA4 = obj->clsPipe3->fkaMid;
			KA1 = obj->CrossType8KA1(KB1, KA2, KA3, KA4, obj->joinPipe1->Area(obj->clsPipe2), obj->joinPipe1->roughness, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->roughness, obj->clsPipe3->Area(obj->clsPipe4), obj->clsPipe3->roughness, obj->clsPipe4->Area(obj->joinPipe1), obj->clsPipe4->roughness);

			KB2 = 1.0 * sqrt(KA1 + KB1) - KA2;
			KB3 = 1.0 * sqrt(KA1 + KB1) - KA3;
			KB4 = 1.0 * sqrt(KA1 + KB1) - KA4;
			obj->joinPipe1->port1VKA = sqrt(KA1);
			obj->clsPipe2->port2VKB = sqrt(KB2);
			obj->clsPipe3->port2VKB = sqrt(KB3);
			obj->clsPipe4->port2VKB = sqrt(KB4);

			break;

		case 9:
			KB1 = obj->clsPipe2->fkbMid;
			KA2 = obj->joinPipe1->fkaMid;
			KA3 = obj->clsPipe4->fkaMid;
			KB4 = obj->clsPipe3->fkbMid;
			KA1 = obj->CrossType9KA1(KB1, KA2, KA3, KB4, obj->joinPipe1->Area(obj->clsPipe2), obj->joinPipe1->roughness, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->roughness, obj->clsPipe3->Area(obj->clsPipe4), obj->clsPipe3->roughness, obj->clsPipe4->Area(obj->joinPipe1), obj->clsPipe4->roughness);
			KB2 = 1.0 * (KA1 + KB1) - KA2;
			KB3 = 1.0 * (KA1 + KB1) - KA3;
			KA4 = 1.0 * (KA1 + KB1) - KB4;
			obj->joinPipe1->port1VKA = sqrt(KA1);
			obj->clsPipe2->port2VKB = sqrt(KA2);
			obj->clsPipe3->port2VKB = sqrt(KB3);
			obj->clsPipe4->port1VKA = sqrt(KA4);

			break;
		case 10:
			KB1 = obj->clsPipe2->fkbMid;
			KA2 = obj->joinPipe1->fkaMid;
			KB3 = obj->clsPipe4->fkbMid;
			KA4 = obj->clsPipe3->fkaMid;
			KA1 = obj->CrossType10KA1(KB1, KA2, KB3, KA4, obj->joinPipe1->Area(obj->clsPipe2), obj->joinPipe1->roughness, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->roughness, obj->clsPipe3->Area(obj->clsPipe4), obj->clsPipe3->roughness, obj->clsPipe4->Area(obj->joinPipe1), obj->clsPipe4->roughness);

			KB2 = 1.0 * sqrt(KA1 + KB1) - KA2;
			KA3 = 1.0 * sqrt(KA1 + KB1) - KB3;
			KB4 = 1.0 * sqrt(KA1 + KB1) - KA4;
			obj->joinPipe1->port1VKA = sqrt(KA1);
			obj->clsPipe2->port2VKB = sqrt(KB2);
			obj->clsPipe3->port1VKA = sqrt(KA3);
			obj->clsPipe4->port2VKB = sqrt(KB4);

			break;

		case 11:
			KA1 = obj->clsPipe2->fkaMid;
			KA2 = obj->joinPipe1->fkaMid;
			KB3 = obj->clsPipe4->fkbMid;
			KA4 = obj->clsPipe3->fkaMid;
			KB1 = obj->CrossType11KA1(KA1, KA2, KB3, KA4, obj->joinPipe1->Area(obj->clsPipe2), obj->joinPipe1->roughness, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->roughness, obj->clsPipe3->Area(obj->clsPipe4), obj->clsPipe3->roughness, obj->clsPipe4->Area(obj->joinPipe1), obj->clsPipe4->roughness);
			KB2 = 1.0 * sqrt(KA1 + KB1) - KA2;
			KA3 = 1.0 * sqrt(KA1 + KB1) - KB3;
			KB4 = 1.0 * sqrt(KA1 + KB1) - KA4;
			obj->joinPipe1->port2VKB = sqrt(KB1);
			obj->clsPipe2->port2VKB = sqrt(KB2);
			obj->clsPipe3->port1VKA = sqrt(KA3);
			obj->clsPipe4->port2VKB = sqrt(KB4);

			break;
		case 12:
			KB1 = obj->clsPipe2->fkbMid;
			KB2 = obj->joinPipe1->fkbMid;
			KB3 = obj->clsPipe4->fkbMid;
			KB4 = obj->clsPipe3->fkbMid;
			KA1 = obj->CrossType12KA1(KB1, KB2, KB3, KB4, obj->joinPipe1->Area(obj->clsPipe2), obj->joinPipe1->roughness, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->roughness, obj->clsPipe3->Area(obj->clsPipe4), obj->clsPipe3->roughness, obj->clsPipe4->Area(obj->joinPipe1), obj->clsPipe4->roughness);

			KA2 = 1.0 * sqrt(KA1 + KB1) - KB2;
			KA3 = 1.0 * sqrt(KA1 + KB1) - KB3;
			KA4 = 1.0 * sqrt(KA1 + KB1) - KB4;
			obj->joinPipe1->port1VKA = sqrt(KA1);
			obj->clsPipe2->port1VKA = sqrt(KA2);
			obj->clsPipe3->port1VKA = sqrt(KA3);
			obj->clsPipe4->port1VKA = sqrt(KA4);

			break;

		case 13:
			KB1 = obj->clsPipe2->fkbMid;
			KB2 = obj->joinPipe1->fkbMid;
			KA3 = obj->clsPipe4->fkaMid;
			KB4 = obj->clsPipe3->fkbMid;
			KA1 = obj->CrossType13KA1(KB1, KB2, KA3, KB4, obj->joinPipe1->Area(obj->clsPipe2), obj->joinPipe1->roughness, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->roughness, obj->clsPipe3->Area(obj->clsPipe4), obj->clsPipe3->roughness, obj->clsPipe4->Area(obj->joinPipe1), obj->clsPipe4->roughness);

			KA2 = 1.0 * sqrt(KA1 + KB1) - KB2;
			KB3 = 1.0 * sqrt(KA1 + KB1) - KA3;
			KA4 = 1.0 * sqrt(KA1 + KB1) - KB4;
			obj->joinPipe1->port1VKA = sqrt(KA1);
			obj->clsPipe2->port1VKA = sqrt(KA2);
			obj->clsPipe3->port2VKB = sqrt(KB3);
			obj->clsPipe4->port1VKA = sqrt(KA4);

			break;

		case 14:
			KB1 = obj->clsPipe2->fkbMid;
			KB2 = obj->joinPipe1->fkbMid;
			KB3 = obj->clsPipe4->fkbMid;
			KA4 = obj->clsPipe3->fkaMid;
			KA1 = obj->CrossType14KA1(KB1, KB2, KB3, KA4, obj->joinPipe1->Area(obj->clsPipe2), obj->joinPipe1->roughness, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->roughness, obj->clsPipe3->Area(obj->clsPipe4), obj->clsPipe3->roughness, obj->clsPipe4->Area(obj->joinPipe1), obj->clsPipe4->roughness);

			KA2 = 1.0 * sqrt(KA1 + KB1) - KB2;
			KA3 = 1.0 * sqrt(KA1 + KB1) - KB3;
			KB4 = 1.0 * sqrt(KA1 + KB1) - KA4;
			obj->joinPipe1->port1VKA = sqrt(KA1);
			obj->clsPipe2->port1VKA = sqrt(KA2);
			obj->clsPipe3->port1VKA = sqrt(KA3);
			obj->clsPipe4->port2VKB = sqrt(KB4);

			break;

		case 15:
			KA1 = obj->clsPipe2->fkaMid;
			KA2 = obj->joinPipe1->fkaMid;
			KA3 = obj->clsPipe4->fkaMid;
			KB4 = obj->clsPipe3->fkbMid;
			KB1 = obj->CrossType15KB1(KA1, KA2, KA3, KB4, obj->joinPipe1->Area(obj->clsPipe2), obj->joinPipe1->roughness, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->roughness, obj->clsPipe3->Area(obj->clsPipe4), obj->clsPipe3->roughness, obj->clsPipe4->Area(obj->joinPipe1), obj->clsPipe4->roughness);
			KB2 = 1.0 * sqrt(KA1 + KB1) - KA2;
			KB3 = 1.0 * sqrt(KA1 + KB1) - KA3;
			KA4 = 1.0 * sqrt(KA1 + KB1) - KB4;
			obj->joinPipe1->port2VKB = sqrt(KB1);
			obj->clsPipe2->port2VKB = sqrt(KB2);
			obj->clsPipe3->port2VKB = sqrt(KB3);
			obj->clsPipe4->port1VKA = sqrt(KA4);

			break;

		case 16:


			KB1 = obj->clsPipe2->fkbMid;
			KB2 = obj->joinPipe1->fkbMid;
			KA3 = obj->clsPipe4->fkaMid;
			KA4 = obj->clsPipe3->fkaMid;
			KA1 = obj->CrossType16KA1(KB1, KB2, KA3, KA4, obj->joinPipe1->Area(obj->clsPipe2), obj->joinPipe1->roughness, obj->clsPipe2->Area(obj->clsPipe3), obj->clsPipe2->roughness, obj->clsPipe3->Area(obj->clsPipe4), obj->clsPipe3->roughness, obj->clsPipe4->Area(obj->joinPipe1), obj->clsPipe4->roughness);

			KA2 = 1.0 * sqrt(KA1 + KB1) - KB2;
			KB3 = 1.0 * sqrt(KA1 + KB1) - KA3;
			KB4 = 1.0 * sqrt(KA1 + KB1) - KA4;

			obj->joinPipe1->port1VKA = sqrt(KA1);
			obj->clsPipe2->port1VKA = sqrt(KA2);
			obj->clsPipe3->port2VKB = sqrt(KB3);
			obj->clsPipe4->port2VKB = sqrt(KB4);

			break;
		default:printf("四通类型错误.\n");

		}

		obj->dblErrP = MyCurP - obj->Ports[4].en_pressure;





	}

	void DoHydraulicBack(CrossStruct*) {

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

	double DoKA(CrossStruct*, double, double, double, double, double, double, double, double) {

		return 0;
	}

	double DoKB(CrossStruct*, double, double, double, double, double, double, double, double) {

		return 0;
	}

	void SwapVal(CrossStruct* obj) {

		if (obj->joinPipe1->Ports[2].JoinCode == obj->intNum) {
			obj->Ports[2].en_pressure = obj->joinPipe1->Ports[1].en_pressure;
			obj->Ports[2].en_quality = -1.0 * obj->joinPipe1->Ports[1].en_quality;
			obj->Ports[2].en_velocity = -1.0 * obj->joinPipe1->uMid;

		}
		else {
			obj->Ports[1].en_pressure = obj->joinPipe1->Ports[2].en_pressure;
			obj->Ports[1].en_quality = obj->joinPipe1->Ports[2].en_quality;
			obj->Ports[1].en_velocity = obj->joinPipe1->uMid;

		}

		if (obj->clsPipe2->Ports[2].JoinCode == obj->intNum) {
			obj->Ports[2].en_pressure = obj->clsPipe2->Ports[1].en_pressure;
			obj->Ports[2].en_quality = -1.0 * obj->clsPipe2->Ports[1].en_quality;
			obj->Ports[2].en_velocity = -1.0 * obj->clsPipe2->uMid;

		}
		else {
			obj->Ports[1].en_pressure = obj->clsPipe2->Ports[2].en_pressure;
			obj->Ports[1].en_quality = obj->clsPipe2->Ports[2].en_quality;
			obj->Ports[1].en_velocity = obj->clsPipe2->uMid;

		}

		if (obj->clsPipe3->Ports[3].JoinCode == obj->intNum) {
			obj->Ports[3].en_pressure = obj->clsPipe3->Ports[1].en_pressure;
			obj->Ports[3].en_quality = -1.0 * obj->clsPipe3->Ports[1].en_quality;
			obj->Ports[3].en_velocity = -1.0 * obj->clsPipe3->uMid;

		}
		else {
			obj->Ports[1].en_pressure = obj->clsPipe3->Ports[2].en_pressure;
			obj->Ports[1].en_quality = obj->clsPipe3->Ports[2].en_quality;
			obj->Ports[1].en_velocity = obj->clsPipe3->uMid;

		}


		if (obj->clsPipe4->Ports[4].JoinCode == obj->intNum) {
			obj->Ports[1].en_pressure = obj->clsPipe4->Ports[2].en_pressure;
			obj->Ports[1].en_quality = obj->clsPipe4->Ports[2].en_quality;
			obj->Ports[1].en_velocity = obj->clsPipe4->uMid;

		}
		else {
			obj->Ports[4].en_pressure = obj->clsPipe4->Ports[1].en_pressure;
			obj->Ports[4].en_quality = -1.0 * obj->clsPipe4->Ports[1].en_quality;
			obj->Ports[4].en_velocity = -1.0 * obj->clsPipe4->uMid;

		}

	}

	double RunThermal(CrossStruct*) {

		return 0;
	}

	double TestConnection(CrossStruct*) {

		return 0;
	}

	double TestTopology(CrossStruct*) {

		return 0;
	}


};

#endif