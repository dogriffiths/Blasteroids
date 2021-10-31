#define KEEP_WITHIN(v, lower, upper) v = ((v) < (lower)) ? (lower) : ((v) > (upper)) ? (upper) : (v)
#define WRAP_WITHIN(v, lower, upper) v = ((v) < (lower)) ? (upper) : ((v) > (upper)) ? (lower) : (v)
#define MOVE(x, y, heading, speed) (x) = (x) + sinf(heading) * (speed), (y) = (y) - cosf(heading) * (speed)

