#ifndef HSG_CONTEXT_H_
#define HSG_CONTEXT_H_

namespace hsg{
	class CoordSystem;
	class GraphicsService;
	class InputService;
	class TimeService;
	class AnimationService;
	class ScoreService;
	class FieldLayout;
	class TaskService;

	struct Context{
		CoordSystem* mCoordService;
		GraphicsService* mGraphicsService;
		InputService* mInputService;
		TimeService* mTimeService;
		AnimationService* mAnimationService;
		ScoreService* mScore;
		FieldLayout* mLayout;
		TaskService* mTaskService;
	};
}

#endif /* HSG_CONTEXT_H_ */
