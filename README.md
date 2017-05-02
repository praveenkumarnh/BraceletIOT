# BraceletIOT

# Bluetooth protocol:
The bracelet reads commands via bluetooth serial with the format <$type,$data>.
The following types can be sent to it:
- <1,Integer> on connection this is the first thing should be sent to the bracelet.
$data represents a unique number of the phone.
as an acknowlegment the bracelet will send back its database with the following format:
[<$type,$time,$tsid,$data>, <$type,$time,$tsid,$data>, ..., <$type,$time,$tsid,$data>]
(records can be tags, app_data or any other things as defined in this doc https://docs.google.com/document/d/1-qHOoyWK5xLiwJvJ40AK0ONJ1xDmyQk-YbECwnUxzqk/edit)

- <2,Integer> - adds new data (such as temperature measurement by doctor).
As an acknowledge bracelet sends # back.
- <3,Integer> - delete record number $data (the index in the order from when sending <1,Integer>).
It doesn't actually deletes, just adds a record into the DB. when phone is showing the list, it should hide deleted records
As an acknowledge bracelet sends # back.
- <4,Integer> - adds a record of headquarter communication (such as evacuation notification),
$data can be an ID of something, better ask course staff
As an acknowledge bracelet sends # back.
- <5,Integer> - adds a record of blood pressure.
$data = blood pressure
As an acknowledge bracelet sends # back.
- <6,Integer> - Turn on buzzer, the $data has no meaning, but should be some kind of integer. 0 can be put there.
As an acknowledge bracelet sends # back.
- <13,Integer> - adds soldier status (severity of injury)
$data is id of the status
As an acknowledge bracelet sends # back.
- <14,???> - will be location - not yet implemented
As an acknowledge bracelet sends # back.
- <15,Integer> - adds a custom record
As an acknowledge bracelet sends # back.

For example, the command <1,123> will add a record into the bracelet that represents a new connection by a phone that is represented by the number 123. As a response you will get the database.

# Wiring:
![alt tag](https://raw.githubusercontent.com/ValkA/BraceletIOT/master/bracelet_bb.png)

# IDE:
Don't forget to include libraries from "Libraries for IDE" folder
TI Documentation about NFC pairing - http://www.ti.com/lit/an/sloa187a/sloa187a.pdf
