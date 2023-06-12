[top]
components : tt@Tracking_Table rx@Scanning_Receiver
in : test_signal brf brid
out : notify bs_id bs_freq
Link : test_signal ext_signal@rx
Link : brf bus_receive_freq@tt
Link : brid bus_receive_id@tt
Link : detected_signal_properties@rx signal_props@tt
Link : new_freq@tt ext_signal@rx
Link : notify@rx notify
Link : bus_send_id@tt bs_id
Link : bus_send_freq@tt bs_freq

[rx]
freq_lower_bound : 18000
freq_upper_bound : 25000

[tt]
table_id : 2