/*******************************************************************
*
*  DESCRIPTION: Atomic Model Tracking_Table
*
*  AUTHOR: Peter MacSweem 
*
*  DATE: 17/10/2003
*
*******************************************************************/

/** include files **/
#include "tracking_table.h" // class Transmitrer
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Tracking_Table
* Description: 
********************************************************************/
Tracking_Table::Tracking_Table( const string &name )
: Atomic( name )
, signal_props( addInputPort( "signal_props" ) )
, bus_receive_freq( addInputPort( "bus_receive_freq" ) )
, bus_receive_id( addInputPort( "bus_receive_id" ) )
, bus_send_id( addOutputPort( "bus_send_id" ) )
, bus_send_freq( addOutputPort( "bus_send_freq" ) )
, new_freq( addOutputPort( "new_freq" ) )
, updateTime( 0, 0, 0, 1 )
, procTime( 0, 0, 0, 5 )
, busTime( 0, 0, 0, 10 )
, notifyTime( 0, 0, 0, 3 )

{
  tableID = 1;
  update_freq = 0;
  localState = wait;

  string stableID( MainSimulator::Instance().getParameter( description(), "table_id" ) ) ;
	if( stableID != "" )
		tableID = str2float(stableID) ;
}


/*******************************************************************
* Function Name: initFunction
* Description: 
********************************************************************/
Model &Tracking_Table::initFunction()
{
  passivate();
  return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Tracking_Table::externalFunction( const ExternalMessage &msg )
{

  if( localState == wait )
  {
    if ( msg.port() == signal_props )
    {
      if ( msg.value() != 0 )
      {
        localState = new_signal_detected;
        update_freq = msg.value();
        this->holdIn( active, procTime ) ;
      }
      else // do not react to a freq of zero
      {
        passivate();
      }
    }
    else if ( msg.port() == bus_receive_freq )
    {
      localState = receive_update_from_bus;
      update_freq = msg.value();
      this->holdIn( active, updateTime ) ;
    }
  }
  
  return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &Tracking_Table::internalFunction( const InternalMessage & )
{

  if( localState == receive_update_from_bus)
  {
    localState = notify_new_freq;
    this->holdIn( active, notifyTime );
  }
  else if( localState == notify_new_freq)
  {
    localState = wait;
    this->holdIn( active, Time::Zero );
  }
  else if ( localState == new_signal_detected )
  {
    localState = send_update_to_bus;
    this->holdIn( active, busTime );
  }
	else if( localState == send_update_to_bus)
  {
    localState = wait;
    this->holdIn( active, Time::Zero );
  }
  else if ( localState == wait )
  {
    passivate();
  }
  
  return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Tracking_Table::outputFunction( const InternalMessage &msg )
{

  if( localState == new_signal_detected )
  {
    sendOutput( msg.time(), bus_send_id, tableID ) ;
    sendOutput( msg.time(), bus_send_freq, update_freq ) ;
  }
  else if( localState == receive_update_from_bus )
  {
    sendOutput( msg.time(), new_freq, update_freq ) ;
  }
  else if ( localState == wait )
  {
    sendOutput( msg.time(), new_freq, 0 ) ;
    sendOutput( msg.time(), bus_send_id, 0 ) ;
    sendOutput( msg.time(), bus_send_freq, 0 ) ;
  }

  return *this ;
}