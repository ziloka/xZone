[Source](https://github.com/shunguang/xZone/blob/6dd946866a1b6a693e1023f0848f9a8c4082552d/src/imagePub/ImagePublisher.cpp#L182-L205)

```cpp
for (uint32_t nSamples = start; nSamples < end; nSamples += step) {
    // there are 1,000,000,000 nanoseconds in a second
    auto nanoseconds_per_msg = std::chrono::nanoseconds(1000000000 / nSamples);

    std::cout << "sending " << nSamples << " samples" << std::endl;
    int cnt = 0;
    for (int cnt = 0; cnt < numSamples; cnt += nSamples) {
        for (uint32_t i = 0; i < nSamples; i++) {
            if (publish(false, nSamples)) {

            }
            std::this_thread::sleep_for(nanoseconds_per_msg);
        }
    }
    std::cout << "sent " << nSamples << " samples" << std::endl;
}
```