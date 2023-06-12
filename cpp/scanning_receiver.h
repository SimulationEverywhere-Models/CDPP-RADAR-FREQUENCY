/*******************************************************************
*
*  DESCRIPTION: Atomic Model Scanning_Receiver
*
*  AUTHOR: Peter MacSweem 
*
*  DATE: 17/10/2003
*
*******************************************************************/

#ifndef __SCANNING_RECEIVER_H
#define __SCANNING_RECEIVER_H

#include <list>
#include "atomic.h"     // class Atomic

class Scanning_Receiver : public Atomic
{
public:
	Scanning_Receiver( const string &name = "Scanning_Receiver" );  //Default constructor
	virtual string className() const ;

protected:
  enum rx_state // define local state definitions (S)
	{
    scan,
    signal_detected,
    process_signal,
    notify
	} ;
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &ext_signal;
	Port &notify_ext;
  Port &detected_signal_properties;
	Time detectionTime;
  Time processTime;
  Time notifyTime;
  rx_state localState;
  Value detected_freq;
  float lower;
  float upper;
};	// class Scanning_Receiver

// ** inline ** // 
inline
string Scanning_Receiver::className() const
{
	return "Scanning_Receiver" ;
}

#endif   //__SCANNING_RECEIVER_H
