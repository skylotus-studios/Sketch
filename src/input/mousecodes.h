#pragma once

struct mousecodes {
    static constexpr int button1 = 0;
    static constexpr int button2 = 1;
    static constexpr int button3 = 2;
    static constexpr int button4 = 3;
    static constexpr int button5 = 4;
    static constexpr int button6 = 5;
    static constexpr int button7 = 6;
    static constexpr int button8 = 7;

    static constexpr int last = button8;
    static constexpr int left = button1;
    static constexpr int right = button2;
    static constexpr int middle = button3;
};

inline mousecodes mouse;