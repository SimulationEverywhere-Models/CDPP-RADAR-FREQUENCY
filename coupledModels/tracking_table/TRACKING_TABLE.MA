[top]
components : tt@Tracking_Table
in : sp brf brid
out : bs_id bs_freq nf
Link : sp signal_props@tt
Link : brf bus_receive_freq@tt
Link : brid bus_receive_id@tt
Link : bus_send_id@tt bs_id
Link : bus_send_freq@tt bs_freq
Link : new_freq@tt nf

[tt]
table_id : 2