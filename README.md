Open this folder in VSCode with PlatformIO extension installed.

To run this in arduino IDE first copy everything in 'lib' folder to Arduino folder in My Document.

Slot Values are stored in an integer array. Default value for array elements is zero.

    [ 0, 0, 0, 0 ]

When a order received array values are set to slot numbers.

    ex 1 : [ 2, 4, 11, 16 ]
    
    ex 2 : [ 1, 15, 17, 0 ]
    
    ex 3 : [ 5, 0, 0, 0 ]

Alone with this 'isProcessing' boolean variable set to true.

So course of action is to track the value of 'isProcessing' variable in loop function and if isProcessing' become true start the process.

    ex :

        void loop()
        {
            if (isProcessing)
            {
                //Start the process here
                //Values for selected slots can be retrieved from slots array.

                for (size_t i = 0; i < 4; i++)
                {
                    if (slots[i] > 0)   //If slot value is grater zero, that slot has been allocated.
                    {
                        Serial.println(slots[i]);
                    }
                } 
            }

            // When robot finish the task, set 'isProcessing' variable to false.

            //Adding delay

            digitalWrite(LED_BUILTIN, HIGH);
            Serial.println("Arduino is Running...");
            delay(1000);

            digitalWrite(LED_BUILTIN, LOW);
            delay(1000);
        }