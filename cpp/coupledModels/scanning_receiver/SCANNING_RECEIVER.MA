[top]
components : rx@Scanning_Receiver
in : test_signal
out : notify props
Link : test_signal ext_signal@rx
Link : notify@rx notify
Link : detected_signal_properties@rx props

[rx]
freq_lower_bound : 18000
freq_upper_bound : 25000