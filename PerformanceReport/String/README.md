MSVC X86_64 O2

[1] SSO 短字符串构造 (10000000 次)
    std::string:    140 ms
    dast::cstring:     94 ms

[2] 长字符串构造 (堆分配, 10000000 次)
    std::string:    562 ms
    dast::cstring:     688 ms

[3] 拷贝构造 (SSO, 10000000 次)
    std::string:    453 ms
    dast::cstring:     62 ms

[4] 随机大小构造 (混合 SSO/堆, 10000000 次)
    std::string:    547 ms
    dast::cstring:     93 ms

[5] 移动构造 (10000000 次)
    std::string:    782 ms
    dast::cstring:     1171 ms