/*******************************************************************
*
*  DESCRIPTION: Atomic Model Transmitter
*
*  AUTHOR: Peter MacSweem 
*
*  DATE: 17/10/2003
*
*******************************************************************/

#ifndef __TRANSMITTER_H
#define __TRANSMITTER_H

#include <list>
#include "atomic.h"     // class Atomic

class Transmitter : public Atomic
{
public:
	Transmitter( const string &name = "Transmitter" );					//Default constructor

	virtual string className() const ;
protected:
  enum tx_state // Set local state definitions (S)
	{
		transmit,
		wait
	} ;
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	Port &pulse_out;
	Time pulseDuration;
  Time pulsePeriod;
  float freq;
  tx_state localState;
};	// class Transmitter

// ** inline ** // 
inline
string Transmitter::className() const
{
	return "Transmitter" ;
}

#endif   //__QUEUE_H
