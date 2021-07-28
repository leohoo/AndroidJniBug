#include <jni.h>
#include <string>
#include <android/log.h>

#define LOGD(...)	__android_log_print(ANDROID_LOG_DEBUG, "TEST", __VA_ARGS__)

static const char* ArrToString(const int* arr, int len)
{
    static char string[1024];
    string[0] = 0;
    char item[100]{};

    for (int i = 0; i < len; i++) {
        int v = arr[i];
        sprintf(item, "%d, ", v);
        strcat(string, item);
    }
    return string;
}

void CallJavaWorker(JNIEnv* env, jobject worker, float *output)
{
    jfloatArray outputArray = env->NewFloatArray(2);

    jclass cls = env->GetObjectClass(worker);
    jmethodID mid = env->GetMethodID(cls, "work", "([F)V");
    if (mid == nullptr) {
        return;
    }

    env->CallVoidMethod(worker, mid, outputArray);
    jfloat* jscore = env->GetFloatArrayElements(outputArray, nullptr);
    output[0] = jscore[0];
    output[1] = jscore[1];
    env->ReleaseFloatArrayElements(outputArray, jscore, 0);
}

extern "C"
JNIEXPORT jint JNICALL
Java_jp_co_normee_bugjni_MainActivity_nativeTest(JNIEnv *env, jobject thiz, jobject worker)
{
    int ret;
    for(int step=0; step<2; step++) {
        if (step == 0) {
            float output[2] = {};
            CallJavaWorker(env, worker, output);
            int sum = (int)(output[0]);
            ret = (int)(output[1]);

            const int LEN = 5;
            int array[LEN] = {8888, 9999, 1, sum, ret};

            LOGD("array = %s", ArrToString(array, LEN));
        }
    }
    return ret;
}

