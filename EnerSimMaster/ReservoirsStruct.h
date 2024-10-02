#pragma once
#ifndef __RESERVOIRS_STRUCT_H__
#define __RESERVOIRS_STRUCT_H__
#include"PipeStruct.h"
#include"PipeComponentsTypeENUM.h"
struct SourceStruct {
	char* srcName;
	int srcCode;
	int srcType;
	int joinPipeCode;
	int joinPortCode;
	double en_pressure;
	double en_quality;
	double en_velocity;
	double en_temperature;
	double elev;
	double vfr;
	PipeStruct* joinPipe1;
	char blnConnected;

	int TubeNum;
	int TubeType;


	double Pz(SourceStruct*) {


		return 0;
	}
	void New1(SourceStruct*) {

	}


	void New2(SourceStruct* obj, int intTheNum, char* strTheName, int intTheType, int intTheConnPiece, int intTheConnPort, double dblTheP, double dblTheQ, double dblTheT) {
		obj->srcCode = intTheNum;

		obj->srcType = intTheType;
		obj->joinPipeCode = intTheConnPiece;
		obj->joinPortCode = intTheConnPort;
		obj->en_pressure = dblTheP;
		obj->en_quality = dblTheQ;
		obj->en_temperature = dblTheT;
		obj->TubeNum = intTheNum;
		obj->TubeType = Source;
	}
	void Init(SourceStruct* obj, PipeStruct* pipe) {
		if (obj->joinPortCode == 1) {
			obj->elev = pipe->elev1;
		}
		else {
			printf("Warning ! ConnError:SrcNo.= %d", obj->srcCode, pipe->PipeCode);
		}
		obj->joinPipe1 = pipe;
	}
	double RhofromPT(double T) {
		PhyproStruct water;
		int myRho;
		myRho = water.RhofromT(T);
		return myRho;
	}
	void Runhyd(SourceStruct* obj) {
		if (obj->srcType == 2) {
			obj->joinPipe1->Ports[2].en_pressure = obj->en_pressure * obj->en_velocity / obj->en_quality;
			obj->joinPipe1->Ports[2].Pfixed = 'N';
			obj->joinPipe1->Ports[2].Ufixed = 'Y';
		}

		if (obj->srcType == 1) {
			obj->vfr = 1.0 * obj->en_quality * obj->en_velocity / obj->en_quality;
			obj->joinPipe1->Ports[1].en_velocity = obj->en_velocity;
			obj->joinPipe1->Ports[1].Pfixed = 'Y';
			obj->joinPipe1->Ports[1].Ufixed = 'N';
		}

	}
	void SwapVal(SourceStruct* obj) {
		if (obj->srcType == 1) {
			obj->en_quality = obj->joinPipe1->Ports[1].en_quality / obj->joinPipe1->Ports[2].en_quality / obj->en_quality;
		}
		if (obj->srcType == 2) {
			obj->en_pressure = obj->joinPipe1->Ports[1].en_pressure * obj->en_quality;
		}
		obj->vfr = 1.0 * obj->en_quality * sqrt(obj->RhofromPT(obj->en_temperature) / obj->en_quality);

	}
	void RunThermal(SourceStruct*) {

	}
	void TestConnection(SourceStruct*) {

	}

};


struct SinkStruct {
	char* sinkName;
	int sinkNumber;
	int sinkType;
	int joinPipeNumber;
	int joinPortNumber;
	double en_pressure;
	double en_quality;
	double en_velocity;
	double en_temperature;
	double elev;
	double vfr;
	PipeStruct* joinPipe1;
	char blnConnected;
	int TubeNum;
	int TubeType;
	double Pz(SinkStruct*) {


		return 0;
	}
	void New1(SinkStruct*) {

	}

	void New2(SinkStruct* obj, int intTheNum, char* strTheName, int intTheType, int intTheConnPiece, int intTheConnPort, double dblTheP, double dblTheQ, double dblTheT) {
		obj->sinkNumber = intTheNum;

		obj->sinkType = intTheType;
		obj->joinPipeNumber = intTheConnPiece;
		obj->joinPortNumber = intTheConnPort;
		obj->en_pressure = dblTheP;
		obj->en_quality = dblTheQ;
		obj->en_temperature = dblTheT;
		obj->TubeNum = intTheNum;
		obj->TubeType = Source;
	}

	void Init(SinkStruct* obj, PipeStruct* pipe) {
		if (obj->joinPortNumber == 2) {
			obj->elev = pipe->elev2;
		}
		else {
			printf("Warning ! ConnError:SinkNo.= %d", obj->sinkNumber, pipe->PipeCode);
		}
		obj->joinPipe1 = pipe;
	}
	double RhofromPT(double T) {
		PhyproStruct water;
		int myRho;
		myRho = water.RhofromT(T);
		return myRho;
	}
	void Runhyd(SinkStruct* obj) {
		if (obj->sinkType == 3) {
			obj->joinPipe1->Ports[2].en_pressure = obj->en_pressure;
			obj->joinPipe1->Ports[2].Pfixed = 'N';
			obj->joinPipe1->Ports[2].Ufixed = 'Y';
		}

		if (obj->sinkType == 4) {
			obj->vfr = 1.0 * obj->en_quality * obj->joinPipe1->Ports[2].en_density;
			obj->en_velocity = 1.0 * obj->vfr * obj->joinPipe1->Ports[2].en_quality;
			obj->joinPipe1->Ports[1].en_velocity = obj->en_velocity;
			obj->joinPipe1->Ports[1].Pfixed = 'Y';
			obj->joinPipe1->Ports[1].Ufixed = 'N';
		}


	}
	void SwapVal(SinkStruct* obj) {
		if (obj->sinkType == 3) {
			obj->en_quality = obj->joinPipe1->Ports[1].en_pressure / obj->joinPipe1->Ports[1].en_velocity;
		}
		if (obj->sinkType == 4) {
			obj->en_pressure = obj->joinPipe1->Ports[1].en_pressure;
		}
		obj->vfr = 1.0 * obj->en_quality * sqrt(obj->RhofromPT(obj->en_temperature));
	}
	void RunThermal(SinkStruct*) {

	}
	void TestConnection(SinkStruct*) {

	}

	void TestTopology(SinkStruct*) {

	}

};

#endif