/*******************************************************************
*
*  DESCRIPTION: Atomic Model Transmitter
*
*  AUTHOR: Peter MacSweem 
*
*  DATE: 17/10/2003
*
*******************************************************************/

/** include files **/
#include "transmitter.h" // class Transmitrer
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )
#include <iostream>
#include <sstream>
using namespace std;

/** public functions **/

/*******************************************************************
* Function Name: Transmitter
* Description: 
********************************************************************/
Transmitter::Transmitter( const string &name )
: Atomic( name )
, pulse_out( addOutputPort( "pulse_out" ) )
, pulseDuration( 0, 0, 0, 5 )
, pulsePeriod( 0, 0, 0, 50 )

{
  localState = wait; // start in wait so at time=0 a transition to transmit can occur
  freq=20000;

  string sfreq( MainSimulator::Instance().getParameter( description(), "frequency" ) ) ;
	if( sfreq != "" )
		freq = str2float(sfreq) ;

	string sPulseTime( MainSimulator::Instance().getParameter( description(), "pulseDuration" ) ) ;
	if( sPulseTime != "" )
		pulseDuration = sPulseTime ;

  string sPeriodTime( MainSimulator::Instance().getParameter( description(), "pulsePeriod" ) ) ;
	if( sPeriodTime != "" )
		pulsePeriod = sPeriodTime ;

}


/*******************************************************************
* Function Name: initFunction
* Description: Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &Transmitter::initFunction()
{
  holdIn( active, Time::Zero );
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Transmitter::externalFunction( const ExternalMessage &msg )
{
  return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &Transmitter::internalFunction( const InternalMessage & )
{
  if( this->localState == transmit)
  {
    localState = wait;
    this->holdIn( active, pulsePeriod - pulseDuration ) ;
  }
  else if ( this->localState == wait )
  {
    localState = transmit;
    this->holdIn( active, pulseDuration ) ;
  }

  return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Transmitter::outputFunction( const InternalMessage &msg )
{
  if( this->localState == transmit )
  {
    sendOutput( msg.time(), pulse_out, 0 ) ;
  }
  else if ( this->localState == wait )
  {
    sendOutput( msg.time(), pulse_out, freq ) ;
  }
  return *this ;
}
