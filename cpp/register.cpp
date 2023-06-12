/*******************************************************************
*
*  DESCRIPTION: Simulator::registerNewAtomics()
*
*  AUTHOR: Amir Barylko & Jorge Beyoglonian 
*
*  EMAIL: mailto://amir@dc.uba.ar
*         mailto://jbeyoglo@dc.uba.ar
*
*  DATE: 27/6/1998
*
*******************************************************************/

#include "modeladm.h" 
#include "mainsimu.h"
#include "queue.h"      // class Queue
#include "generat.h"    // class Generator
#include "cpu.h"        // class CPU
#include "transduc.h"   // class Transducer
#include "trafico.h"    // class Trafico
#include "tracking_table.h" // class Scanning_Receiver
#include "transmitter.h" // class Transmitter
#include "scanning_receiver.h" // class Scanning_Receiver

void MainSimulator::registerNewAtomics()
{
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Queue>() , "Queue" ) ;
	//SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Generator>() , "Generator" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<CPU>() , "CPU" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Transducer>() , "Transducer" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Trafico>() , "Trafico" ) ;
  SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Tracking_Table>() , "Tracking_Table" ) ;
  SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Transmitter>() , "Transmitter" ) ;
  SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Scanning_Receiver>() , "Scanning_Receiver" ) ;

}
