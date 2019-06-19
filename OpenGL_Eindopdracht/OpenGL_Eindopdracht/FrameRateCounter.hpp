#ifndef FRAME_RATE_COUNTER_HPP
#define FRAME_RATE_COUNTER_HPP

#include <deque>

class FrameRateCounter
{
public:
	FrameRateCounter();
	~FrameRateCounter();

	void update(float deltaTime);
	float getAverageFramesPerSecond() const;
private:
#define MAXIMUM_SAMPLES 100
	float totalSeconds;
	float averageFramesPerSecond;
	float currentFramesPerSecond;
	float prevCorrectFrame;
	std::deque<float> sampleBuffer;

	static float getQueueAvg(std::deque<float> q);
};
#endif // !FRAME_RATE_COUNTER_HPP