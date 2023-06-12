/*******************************************************************
*
*  DESCRIPTION: Atomic Model Scanning_Receiver
*
*  AUTHOR: Peter MacSweem 
*
*  DATE: 17/10/2003
*
*******************************************************************/

/** include files **/
#include "scanning_receiver.h" // class Transmitrer
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Scanning_Receiver
* Description: 
********************************************************************/
Scanning_Receiver::Scanning_Receiver( const string &name )
: Atomic( name )
, ext_signal( addInputPort( "ext_signal" ) )
, notify_ext( addOutputPort( "notify" ) )
, detected_signal_properties( addOutputPort( "detected_signal_properties" ) )
, detectionTime( 0, 0, 0, 1 )
, processTime( 0, 0, 0, 10 )
, notifyTime( 0, 0, 0, 30 )

{
  localState = scan; // start in wait so at time=0 a transition to transmit can occur
  detected_freq = 0;
  lower = 0;
  upper = 0;

  string slower( MainSimulator::Instance().getParameter( description(), "freq_lower_bound" ) ) ;
	if( slower != "" )
		lower = str2float(slower);
  string supper( MainSimulator::Instance().getParameter( description(), "freq_upper_bound" ) ) ;
  if( supper != "" )
		upper = str2float(supper);
}


/*******************************************************************
* Function Name: initFunction
* Description: 
********************************************************************/
Model &Scanning_Receiver::initFunction()
{
  passivate();
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Scanning_Receiver::externalFunction( const ExternalMessage &msg )
{
	if( this->localState == scan )
  {
    if ( msg.port() == ext_signal )
    {
      if ( msg.value() != 0 )
      {
        // check to see if it is within our scanning range
        if ( (lower <= msg.value()) && (msg.value() <= upper) )
        {
          localState = signal_detected;
          detected_freq = msg.value();
          this->holdIn( active, detectionTime ) ;
        }
        else // do not react - outside our range
        {
          passivate();
        }
      }
      else // do not react to a signal freq of zero
      {
        passivate();
      }
    }
  }

  return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &Scanning_Receiver::internalFunction( const InternalMessage & )
{
  if ( this->localState == signal_detected )
  {
    localState = process_signal;
    this->holdIn( active, processTime );
  }
  else if ( this->localState == process_signal )
  {
    localState = notify;
    this->holdIn( active, notifyTime );
  }
  else if ( this->localState == notify )
  {
    localState = scan;
    passivate();
  }
  return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Scanning_Receiver::outputFunction( const InternalMessage &msg )
{
	if( this->localState == signal_detected )
  {
    sendOutput( msg.time(), notify_ext, 1 ) ;
  }
  else if ( this->localState == process_signal )
  {
    sendOutput( msg.time(), detected_signal_properties, detected_freq ) ;
  }
  else if ( this->localState == notify )
  {
    detected_freq = 0;
    sendOutput( msg.time(), notify_ext, 0 ) ;
    sendOutput( msg.time(), detected_signal_properties, 0 ) ;
  }
  return *this ;
}
