/* Shared Use License: This file is owned by Derivative Inc. (Derivative)
* and can only be used, and/or modified for use, in conjunction with
* Derivative's TouchDesigner software, and only if you are a licensee who has
* accepted Derivative's TouchDesigner license or assignment agreement
* (which also govern the use of this file). You may share or redistribute
* a modified version of this file provided the following conditions are met:
*
* 1. The shared file or redistribution must retain the information set out
* above and this list of conditions.
* 2. Derivative's name (Derivative Inc.) or its trademarks may not be used
* to endorse or promote products derived from this file without specific
* prior written permission from Derivative.
*/

#include "RGBtoRGBWCHOP.h"

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <assert.h>

extern "C"
{

DLLEXPORT
void
FillCHOPPluginInfo(CHOP_PluginInfo *info)
{
	info->apiVersion = CHOPCPlusPlusAPIVersion;
	info->customOPInfo.opType->setString("Rgbtorgbw");
	info->customOPInfo.opLabel->setString("RGB to RGBW");
	info->customOPInfo.authorName->setString("Richard Burns");
	info->customOPInfo.authorEmail->setString("richard@richandmiyu.com");
	info->customOPInfo.minInputs = 1;
	info->customOPInfo.maxInputs = 1;
}

DLLEXPORT
CHOP_CPlusPlusBase*
CreateCHOPInstance(const OP_NodeInfo* info)
{
	return new RGBtoRGBWCHOP(info);
}

DLLEXPORT
void
DestroyCHOPInstance(CHOP_CPlusPlusBase* instance)
{
	delete (RGBtoRGBWCHOP*)instance;
}

};


RGBtoRGBWCHOP::RGBtoRGBWCHOP(const OP_NodeInfo* info) : myNodeInfo(info)
{

}

RGBtoRGBWCHOP::~RGBtoRGBWCHOP()
{

}

void
RGBtoRGBWCHOP::getGeneralInfo(CHOP_GeneralInfo* ginfo, const OP_Inputs* inputs, void* reserved1)
{
	ginfo->cookEveryFrameIfAsked = false;
	ginfo->timeslice = false;
	ginfo->inputMatchIndex = 0;
}

bool
RGBtoRGBWCHOP::getOutputInfo(CHOP_OutputInfo* info, const OP_Inputs* inputs, void* reserved1)
{
		info->numChannels = 4;
		info->sampleRate = 60;
		return true;
}

void
RGBtoRGBWCHOP::getChannelName(int32_t index, OP_String *name, const OP_Inputs* inputs, void* reserved1)
{
	switch (index) {
	case 0:
		name->setString("r");
		break;
	case 1:
		name->setString("g");
		break;
	case 2:
		name->setString("b");
		break;
	case 3:
		name->setString("w");
		break;
	}
}

void
RGBtoRGBWCHOP::execute(CHOP_Output* output,
							  const OP_Inputs* inputs,
							  void* reserved)
{

	if (inputs->getNumInputs() > 0)
	{
		const OP_CHOPInput	*cinput = inputs->getInputCHOP(0);

		if (cinput->numChannels > 2) 
		{


			for (int s = 0; s < cinput->numSamples; s++)
			{
				r = cinput[0].channelData[0][s];
				g = cinput[0].channelData[1][s];
				b = cinput[0].channelData[2][s];

				res = ConvertToRGBW(r, g, b);

				output->channels[0][s] = res.r;
				output->channels[1][s] = res.g;
				output->channels[2][s] = res.b;
				output->channels[3][s] = res.w;
			}

		}

		else 
		{

			output->channels[0][0] = 0.0;
			output->channels[1][0] = 0.0;
			output->channels[2][0] = 0.0;
			output->channels[3][0] = 0.0;
		}

	}
	else
	{
		output->channels[0][0] = 0.0;
		output->channels[1][0] = 0.0;
		output->channels[2][0] = 0.0;
		output->channels[3][0] = 0.0;
	}
}

int32_t
RGBtoRGBWCHOP::getNumInfoCHOPChans(void * reserved1)
{
	return 0;
}

void
RGBtoRGBWCHOP::getInfoCHOPChan(int32_t index,
										OP_InfoCHOPChan* chan,
										void* reserved1)
{
}

bool		
RGBtoRGBWCHOP::getInfoDATSize(OP_InfoDATSize* infoSize, void* reserved1)
{
	infoSize->rows = 0;
	infoSize->cols = 0;
	infoSize->byColumn = false;
	return true;
}

void
RGBtoRGBWCHOP::getInfoDATEntries(int32_t index,
										int32_t nEntries,
										OP_InfoDATEntries* entries, 
										void* reserved1)
{
	
}

void
RGBtoRGBWCHOP::setupParameters(OP_ParameterManager* manager, void *reserved1)
{
	
}

void 
RGBtoRGBWCHOP::pulsePressed(const char* name, void* reserved1)
{
	
}

