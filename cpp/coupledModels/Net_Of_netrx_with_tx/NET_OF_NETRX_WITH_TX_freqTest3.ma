[top]
components : tr1@Transmitter tr2@Transmitter tr3@Transmitter netrx1 netrx2
out : notify1 notify2 notify3
Link : pulse_out@tr1 ext_signal@netrx1
Link : pulse_out@tr1 ext_signal@netrx2
Link : pulse_out@tr2 ext_signal@netrx1
Link : pulse_out@tr2 ext_signal@netrx2
Link : pulse_out@tr3 ext_signal@netrx1
Link : pulse_out@tr3 ext_signal@netrx2

Link : notify@netrx1 notify1
Link : notify@netrx2 notify2

Link : bs_id@netrx1 brid@netrx2
Link : bs_id@netrx2 brid@netrx1
Link : bs_freq@netrx1 brf@netrx2
Link : bs_freq@netrx2 brf@netrx1


[netrx1]
components : tt1@Tracking_Table rx1@Scanning_Receiver
in : ext_signal brf brid
out : notify bs_id bs_freq
Link : ext_signal ext_signal@rx1
Link : brf bus_receive_freq@tt1
Link : brid bus_receive_id@tt1
Link : detected_signal_properties@rx1 signal_props@tt1
Link : new_freq@tt1 ext_signal@rx1
Link : notify@rx1 notify
Link : bus_send_id@tt1 bs_id
Link : bus_send_freq@tt1 bs_freq

[rx1]
freq_lower_bound : 18000
freq_upper_bound : 20000

[tt1]
table_id : 1

[netrx2]
components : tt2@Tracking_Table rx2@Scanning_Receiver
in : ext_signal brf brid
out : notify bs_id bs_freq
Link : ext_signal ext_signal@rx2
Link : brf bus_receive_freq@tt2
Link : brid bus_receive_id@tt2
Link : detected_signal_properties@rx2 signal_props@tt2
Link : new_freq@tt2 ext_signal@rx2
Link : notify@rx2 notify
Link : bus_send_id@tt2 bs_id
Link : bus_send_freq@tt2 bs_freq

[rx2]
freq_lower_bound : 21000
freq_upper_bound : 22000

[tt2]
table_id : 2


[tr1]
frequency : 17000
pulseDuration : 00:00:00:5
pulsePeriod : 00:00:00:40

[tr2]
frequency : 21500
pulseDuration : 00:00:00:10
pulsePeriod : 00:00:00:20

[tr3]
frequency : 21800
pulseDuration : 00:00:00:10
pulsePeriod : 00:00:00:25
