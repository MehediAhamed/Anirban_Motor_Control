const int arr[] = {6, 7, 8, 9, 10, 11, 12, 13};

void setup() {
    for (int i = 0; i < 8; i ++)
        pinMode(arr[i], OUTPUT);
}

void loop() {
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);
}
