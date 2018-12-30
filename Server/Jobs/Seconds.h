#pragma once

class Seconds {
    private:
        Seconds();
    public:
        static int FromMinutes(int minutes) {
            return minutes * 60;
        }
}