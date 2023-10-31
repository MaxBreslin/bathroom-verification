
# bathroom-verification

This is the current codebase for Forest Grove High School's bathroom verification project. main will be running on a Raspberry Pi embedded in the door lock.

Upon interaction, the below steps will be performed on the Pi:
 1. poll keypad, waiting for student to type in their id and press 'accept' button
 2. send POST request to remote server - example request data below
    ```javascript
    {
        "student-id": "000000",
        "timestamp": "0000000000",
        "bathroom-id": "0"
    }
    ```
We will store this data for future analysis.
