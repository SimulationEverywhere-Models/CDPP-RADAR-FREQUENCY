[newCoupledModel]
components : Scanning_receiver0 Tracking_Table6 
out : notify bus_send_freq bus_send_id 
in : test_signal bus_receive_freq bus_receive_id 
Link : test_signal ext_signal@Scanning_receiver0
Link : bus_receive_freq bus_receive_freq@Tracking_Table6
Link : bus_receive_id bus_receive_freq@Tracking_Table6
Link : new_freq@Tracking_Table6 ext_signal@Scanning_receiver0
Link : detected_signal_properties@Scanning_receiver0 signal_props@Tracking_Table6
Link : notify@Scanning_receiver0 notify
Link : bus_send_freq@Tracking_Table6 bus_send_freq
Link : bus_send_id@Tracking_Table6 bus_send_id

[Scanning_receiver0]
source : Rx.CDD

[Tracking_Table6]
source : Table.CDD

