[top]
components : tr@Transmitter netrx
in : brf brid
out : notify bs_id bs_freq
Link : brf brf@netrx
Link : brid brid@netrx
Link : pulse_out@tr ext_signal@netrx
Link : notify@netrx notify
Link : bs_id@netrx bs_id
Link : bs_freq@netrx bs_freq

[netrx]
components : tt@Tracking_Table rx@Scanning_Receiver
in : ext_signal brf brid
out : notify bs_id bs_freq
Link : ext_signal ext_signal@rx
Link : brf bus_receive_freq@tt
Link : brid bus_receive_id@tt
Link : detected_signal_properties@rx signal_props@tt
Link : new_freq@tt ext_signal@rx
Link : notify@rx notify
Link : bus_send_id@tt bs_id
Link : bus_send_freq@tt bs_freq

[rx]
freq_lower_bound : 22000
freq_upper_bound : 25000

[tt]
table_id : 1

[tr]
frequency : 24000
pulseDuration : 00:00:00:5
pulsePeriod : 00:00:00:40
