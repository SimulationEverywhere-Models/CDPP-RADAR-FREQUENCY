# Frequency Test #1 - No Frequencies detected
..\..\..\simu -mNET_OF_NETRX_WITH_TX_freqTest1.ma -t00:00:00:300 -lnet_of_netrx_with_tx_freqTest1.log -onet_of_netrx_with_tx_freqTest1.out

# Frequency Test #2 - Receiver 1 detection only
..\..\..\simu -mNET_OF_NETRX_WITH_TX_freqTest2.ma -t00:00:00:300 -lnet_of_netrx_with_tx_freqTest2.log -onet_of_netrx_with_tx_freqTest2.out

# Frequency Test #2 - Receiver 2 detection only
..\..\..\simu -mNET_OF_NETRX_WITH_TX_freqTest3.ma -t00:00:00:300 -lnet_of_netrx_with_tx_freqTest3.log -onet_of_netrx_with_tx_freqTest3.out

# Frequency Test #2 - Both Receivers detect
..\..\..\simu -mNET_OF_NETRX_WITH_TX_freqTest4.ma -t00:00:00:300 -lnet_of_netrx_with_tx_freqTest4.log -onet_of_netrx_with_tx_freqTest4.out
