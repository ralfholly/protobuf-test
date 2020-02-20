import com.example.protobuftest.CurrentDateTime.CurrentDateTimeMessage;
import java.io.*;

class CurrentDateTimeTest {

    CurrentDateTimeMessage buildMessage() {
        CurrentDateTimeMessage.Builder msg = CurrentDateTimeMessage.newBuilder();
        msg.setTitle("A simple test #2");
        msg.setCounter(43);
        CurrentDateTimeMessage.Date.Builder date = CurrentDateTimeMessage.Date.newBuilder();
        date.setDay(12);
        date.setMonth(10);
        date.setYear(2002);
        date.setWeekday("Tuesday");
        msg.setDate(date);
        return msg.build();
    }

    boolean storeMessage(CurrentDateTimeMessage msg, String fname) {
        boolean success = false;
        FileOutputStream output = null;
        try {
            output = new FileOutputStream(fname);
            msg.writeTo(output);
            output.close();
            success = true;
        } catch (Exception e) {
            ;
        }
        return success;
    }

    CurrentDateTimeMessage loadMessage(String fname) {
        CurrentDateTimeMessage msg = null;
        FileInputStream input = null;
        try {
            input = new FileInputStream(fname);
            msg = CurrentDateTimeMessage.parseFrom(input);
            input.close();
        } catch (Exception e) {
            ;
        }
        return msg;
    }

   void printMessage(CurrentDateTimeMessage msg) {
        System.out.println("Received a message:");
        System.out.printf("\tTitle: %s\n", msg.getTitle());
        System.out.printf("\tCounter: %d\n", msg.getCounter());
        if (msg.hasDate()) {
            CurrentDateTimeMessage.Date date = msg.getDate();
            System.out.printf("\t%s, %d-%02d-%02d\n", date.getWeekday(), date.getYear(), date.getMonth(), date.getDay());
        } else {
            System.out.println("No date element found!");
        }
        if (msg.hasTime()) {
            CurrentDateTimeMessage.Time time = msg.getTime();
            System.out.printf("\t%02d:%02d:%02d\n", time.getHours(), time.getMinutes(), time.getSeconds());
        } else {
            System.out.println("No time element found!");
        }
   }

   public static final void main(String[] args) {
       if (args.length == 0) {
           System.err.println("Please provide a filename!");
           System.exit(1);
       }
       CurrentDateTimeTest instance = new CurrentDateTimeTest();
       String fname = args[0];
       if (!new File(fname).exists()) {
           System.out.println("Creating current date/time entry");
           CurrentDateTimeMessage msg = instance.buildMessage();
           instance.storeMessage(msg, fname);
       }
       CurrentDateTimeMessage msg2 = instance.loadMessage(fname);
       instance.printMessage(msg2);
   }
}

