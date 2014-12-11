#include "mjAnimator.h"
namespace mjEngine{

mjAnimator::mjAnimator()
{
    //ctor
}

mjAnimator::~mjAnimator()
{
    //dtor
}

void mjAnimator::UpdatePose(float t, mjModelPose& pose, mjAnimation& animation)
{
    unsigned segmentIndexMax = animation.segments.size();


    for (unsigned segmentIndex = 0; segmentIndex < segmentIndexMax; segmentIndex++ )
    {
        float t_segment = t;
        // Figure out in which segment we are.

        mjAnimationSegment* segment = animation.segments[segmentIndex];

        if (segment->meshNum != -1)
        {
            int previousKeyframeNum = 0;
            int nextKeyframeNum = 0;

            // If t_segment > totalTime of the the segment, subtract the time for as many loops as needed.
            // Though in theory, t is always expected to be within the segment's total time or at most slightly over it
            // when crossing from one loop to the next.
            while (t_segment > segment->totalTime)
            {
                t_segment -= segment->totalTime;
            }

            // Find which keyframe we are in for this segment.
            //FIXME: this could probably be optimised.
            while (
                   (nextKeyframeNum < segment->keyframes.size()) &&
                   (t_segment >= segment->keyframes[nextKeyframeNum]->timeStamp)

                   )
                   {
                       nextKeyframeNum++;
                   }

                   previousKeyframeNum = nextKeyframeNum-1;

                   // Perform the interpolation.
                   // Fixme: for now only linear. But more animation types will be supported in the future
                   // FIXME: for now the angle "direction" isn't taken into account, but it should be.
                   mjVector3 angles(segment->keyframes[previousKeyframeNum].angles);
                   mjVector3 delta(segment->keyframes[nextKeyframeNum].angles);

                   delta.Subtract(angles);

                   // Add delta vector to "current" vector, scaled by "time percentage"

                   float t_percentage = (t_segment - segment.keyframes[previousKeyframeNum]->timeStamp)/(segment->keyframes[nextKeyframeNum]->timeStamp - segment->keyframes[previousKeyframeNum]->timeStamp);

                   // Perform interpolation
                   angles.ScaleAdd(t_percentage, delta);

                   // Update pose angles with the result.
                   pose.angles[segment->meshNum]->CopyFrom(angles);

        }
    }

}

}
