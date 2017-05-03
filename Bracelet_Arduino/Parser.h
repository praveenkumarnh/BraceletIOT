// JSON_Formatter.h

#ifndef _PARSER_H
#define _PARSER_H

#include "NFC_Tags_Container.h"

//output format is <$type,$time,$tsid,$data>
Stream& operator<<(Stream& stream, const LogRecord& record) {
    stream.print(F("<"));
    stream.print(record.type);
    stream.print(",");
    stream.print(record.timestamp.time);
    stream.print(",");
    stream.print(record.timestamp.id);
    stream.print(",");

    switch (record.type){
		case tag_scan:
            stream.print(record.data.tagId);
		break;
		case mobile_device_id:
            stream.print(record.data.mobileIdData);
		break;
		case app_new_data:
            stream.print(record.data.rawData);
		break;
		case app_update_data:
            stream.print(record.data.rawData);
		break;
		case app_headquarter_communication:
            stream.print(record.data.rawData);
		break;
		case blood_pressure:
            stream.print(record.data.rawData);
		break;
		case app_command:
            stream.print(record.data.rawData);
		break;
		case app_soldier_status:
            stream.print(record.data.statusData);
		break;
		case app_location:
            stream.print(F("1.123,1.232")); // not yet implemented
		break;
		case custom:
            stream.print(record.data.rawData);
		break;
        default:
            stream.print(record.data.rawData);
        break;
    }

    stream.print(F(">"));
    return stream;
}

// input format is <$type,$data>
// return true iff success
bool operator>>(Stream& stream, LogRecord& record) {
    if(stream.read() != '<'){
        return false;
    }

    Data_Type type = stream.parseInt();
    if(stream.read() != ','){
        return false;
    }

    Data data;
    switch (type){
		// case tag_scan: tags are recieved via NFC and not via bluetooth
        //     data.tagId = stream.parseInt();
		// break;
		case mobile_device_id:
            data.mobileIdData = stream.parseInt();
		break;
		case app_new_data:
            data.rawData = stream.parseInt();
		break;
		case app_update_data:
            data.rawData = stream.parseInt();
		break;
		case app_headquarter_communication:
            data.rawData = stream.parseInt();
		break;
		case blood_pressure:
            data.rawData = stream.parseInt();
		break;
		case app_command:
            data.rawData = stream.parseInt();
		break;
		case app_soldier_status:
            data.statusData = stream.parseInt();
		break;
		case app_location:
            data.rawData = -1;//TODO: implement location
		break;
		case custom:
            data.rawData = stream.parseInt();
		break;
        default:
            return false;
        break;
    }

    if(stream.read() != '>'){
        return false;
    }

    record = LogRecord(type, data);
    return true;
}

Stream& operator<<(Stream& stream, LogContainer& container){
  stream.print('[');
  for (int i = 0; i < container.size; i++) {
    stream << container.records[i];
  }
  stream.println("]");
}

#endif