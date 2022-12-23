#include <conio.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

struct Emotion
{
    float freedom;
    float positivity;
    float engagement;
    std::string feeling;
    std::string impulse;
    std::string expression;
};

#define EMOTION_LO 0.3333
#define EMOTION_HI 0.6666
#define EMOTION_MX 1.0000
#define EMOTION_NUM 27

struct Emotion emotions[EMOTION_NUM] =
{
    { EMOTION_LO,EMOTION_LO,EMOTION_LO, "distressed",     "retreat",  "glow red,say whimper,motion retreat" },
    { EMOTION_HI,EMOTION_LO,EMOTION_LO, "lonely",         "whimper",  "glow yellow,say whimper,pose wait" },
    { EMOTION_MX,EMOTION_LO,EMOTION_LO, "alone",          "search",   "glow blue,say hunt,motion search" },
    { EMOTION_LO,EMOTION_LO,EMOTION_HI, "aggressive",     "growl",    "glow red,say growl,pose fight" },
    { EMOTION_HI,EMOTION_LO,EMOTION_HI, "sad",            "paw",      "glow yellow,say mrewl,motion pawshake" },
    { EMOTION_MX,EMOTION_LO,EMOTION_HI, "resigned",       "stare",    "glow blue,say nothing,pose wait" },
    { EMOTION_LO,EMOTION_LO,EMOTION_MX, "uncomfortable",  "wait",     "glow red,say hmewl,pose wait" },
    { EMOTION_HI,EMOTION_LO,EMOTION_MX, "mopey",          "mope",     "glow yellow,say nothing,pose wait" },
    { EMOTION_MX,EMOTION_LO,EMOTION_MX, "interested",     "watch",    "glow blue,say nothing,pose wait" },
      
    { EMOTION_LO,EMOTION_HI,EMOTION_LO, "shy",            "cower",    "" },
    { EMOTION_HI,EMOTION_HI,EMOTION_LO, "detached",       "search",   "" },
    { EMOTION_MX,EMOTION_HI,EMOTION_LO, "skeptical",      "search",   "" },
    { EMOTION_LO,EMOTION_HI,EMOTION_HI, "unsure",         "whine",    "" },
    { EMOTION_HI,EMOTION_HI,EMOTION_HI, "centered",       "nothing",  "" },
    { EMOTION_MX,EMOTION_HI,EMOTION_HI, "focused",        "continue", "" },
    { EMOTION_LO,EMOTION_HI,EMOTION_MX, "hesitant",       "wait",     "" },
    { EMOTION_HI,EMOTION_HI,EMOTION_MX, "engaged",        "be",       "" },
    { EMOTION_MX,EMOTION_HI,EMOTION_MX, "decisive",       "be",       "" },
      
    { EMOTION_LO,EMOTION_MX,EMOTION_LO, "shy",            "mewl",     "" },
    { EMOTION_HI,EMOTION_MX,EMOTION_LO, "calm",           "mew",      "" },
    { EMOTION_MX,EMOTION_MX,EMOTION_LO, "nice",           "sing",     "" },
    { EMOTION_LO,EMOTION_MX,EMOTION_HI, "waiting",        "wait",     "" },
    { EMOTION_HI,EMOTION_MX,EMOTION_HI, "happy",          "be",       "" },
    { EMOTION_MX,EMOTION_MX,EMOTION_HI, "proud",          "be",       "" },
    { EMOTION_LO,EMOTION_MX,EMOTION_MX, "curious",        "wait",     "" },
    { EMOTION_HI,EMOTION_MX,EMOTION_MX, "playful",        "play",     "" },
    { EMOTION_MX,EMOTION_MX,EMOTION_MX, "ecstastic",      "be",       "" },
};


const Emotion *FeelingToName(float freedom, float positivity, float engagement)
{
    for (int i = 0; i < EMOTION_NUM; i++)
    {
        Emotion *e = &emotions[i];
        if (freedom <= e->freedom 
            && positivity <= e->positivity
            && engagement <= e->engagement)
            return e;
    }
    return NULL;
}

class EmotionalPoint
{
public:
    float Confidence = 0.5f; //Confidence
    float Positivity = 0.5f; //Positivity
    float Engagement = 0.5f; //Engagement
    float dirX = 0;
    float dirY = 0;
    float dirZ = 0;
    float spanX = 0;
    float spanY = 0;
    float spanZ = 0;
public:
    EmotionalPoint(float c, float p, float e)
    {
        this->Confidence = c;
        this->Positivity = p;
        this->Engagement = e;
    }
};


class EmotionalCore;

class IEmotive
{
public:
    bool active = true;
    void BiasPos(float &value, float bias)
    {
        value = value * bias;
    }
    void BiasNeg(float& value, float bias)
    {
        value = value / bias;
    }

    virtual void ApplyTo(EmotionalCore& ec) {}

    virtual void Clamp(float& v)
    {
        if (v < 0) v = 0;
        if (v > 1) v = 1;
    }
};

class SensoryState
{
public:
    int tick;
    int ultrasoundDistance;
    int numLifeforms;
};

class EmotionalCore
{
public:
    EmotionalPoint basis;
    EmotionalPoint current;
    std::vector<IEmotive*> emotives;
    SensoryState senses;

    EmotionalCore(float bx, float by, float bz)
    {
        basis.Confidence = bx;
        basis.Positivity = by;
        basis.Engagement = bz;
             
        current = EmotionalPoint(0.5f, 0.5f, 0.5f);
    }
    void print()
    {
        const Emotion *emotion = FeelingToName(current.Confidence, current.Positivity, current.Engagement);
        std::cout << std::to_string(senses.tick)
            << "] " 
            << "Confidence=" << std::to_string((int)(current.Confidence * 100)) << "%, "
            << "Positivity=" << std::to_string((int)(current.Positivity * 100)) << "%, "
            << "Engagement=" << std::to_string((int)(current.Engagement * 100)) << "%  "
            << "= " << emotion->feeling
            << ", " << emotion->impulse
            /* << std::to_string(current.dirX) << ", "
            << std::to_string(current.dirY) << ", "
            << std::to_string(current.dirZ) << " : "
            << std::to_string(current.spanX) << ", "
            << std::to_string(current.spanY) << ", "
            << std::to_string(current.spanZ) << ")"*/
            << std::endl;
    }
    void poll()
    {
        for (int e = 0; e < emotives.size(); e++)
        {
            IEmotive * pEmotive = emotives[e];
            if (pEmotive->active)
                pEmotive->ApplyTo(*this);
        }
        senses.tick++;
    }
};

#define BIAS_VERYSLOW 1.001f
#define BIAS_SLOW 1.05f
#define BIAS_MID  1.01f
#define BIAS_FAST 1.1f

class EmotiveHomeostasis : public IEmotive
{
public:
    float bias = BIAS_VERYSLOW;
    void ApplyTo(EmotionalCore& ec)
    {
        //Seek homeostasis
        if (ec.current.Confidence < ec.basis.Confidence) ec.current.Confidence *= bias;
        else if (ec.current.Confidence > ec.basis.Confidence) ec.current.Confidence /= bias;

        if (ec.current.Positivity < ec.basis.Positivity) ec.current.Positivity *= bias;
        else if (ec.current.Positivity > ec.basis.Positivity) ec.current.Positivity /= bias;

        if (ec.current.Engagement < ec.basis.Engagement) ec.current.Engagement *= bias;
        else if (ec.current.Engagement > ec.basis.Engagement) ec.current.Engagement /= bias;

        Clamp(ec.current.Confidence);
        Clamp(ec.current.Positivity);
        Clamp(ec.current.Engagement);
    }
};


class EmotiveBlocked : public IEmotive
{
public:
    float bias = BIAS_MID;
    void ApplyTo(EmotionalCore& ec)
    {
        if (ec.senses.ultrasoundDistance == 0) {}
        else if (ec.senses.ultrasoundDistance < 10)  BiasNeg(ec.current.Confidence, BIAS_FAST);
        else if (ec.senses.ultrasoundDistance < 35)  BiasNeg(ec.current.Confidence, BIAS_MID);
        else if (ec.senses.ultrasoundDistance < 60)  BiasPos(ec.current.Confidence, BIAS_SLOW);
        else if (ec.senses.ultrasoundDistance < 105) BiasPos(ec.current.Confidence, BIAS_SLOW);
        else if (ec.senses.ultrasoundDistance > 105) BiasPos(ec.current.Confidence, BIAS_FAST);
        Clamp(ec.current.Confidence);
    }
};

class EmotiveSocial : public IEmotive
{
public:
    float bias = BIAS_MID;
    void ApplyTo(EmotionalCore& ec)
    {
        if (ec.senses.numLifeforms == 0) BiasNeg(ec.current.Engagement, BIAS_SLOW);
        else if (ec.senses.numLifeforms == 1) BiasPos(ec.current.Engagement, BIAS_MID);
        else BiasPos(ec.current.Engagement, BIAS_FAST);
        Clamp(ec.current.Engagement);
    }
};

int main()
{
    EmotionalCore ec(0.5f, 0.5f, 0.5f);

    ec.emotives.push_back(new EmotiveHomeostasis());
    ec.emotives.push_back(new EmotiveBlocked());
    ec.emotives.push_back(new EmotiveSocial());

    char ch = '~';
    while (ch != ' ')
    {
        if (_kbhit()) {
            ch = _getch();
            switch (ch)
            {
            case 'q': std::cout << "UltraSound = 5" << std::endl; ec.senses.ultrasoundDistance = 5; break;
            case 'w': std::cout << "UltraSound = 15" << std::endl; ec.senses.ultrasoundDistance = 15; break;
            case 'e': std::cout << "UltraSound = 55" << std::endl; ec.senses.ultrasoundDistance = 55; break;
            case 'r': std::cout << "UltraSound = 105" << std::endl; ec.senses.ultrasoundDistance = 105; break;
            case 't': std::cout << "UltraSound = 1000" << std::endl; ec.senses.ultrasoundDistance = 1000; break;

            case '0': std::cout << "Lifeforms = 0" << std::endl; ec.senses.numLifeforms = 0; break;
            case '1': std::cout << "Lifeforms = 1" << std::endl; ec.senses.numLifeforms = 1; break;
            case '2': std::cout << "Lifeforms = 2" << std::endl; ec.senses.numLifeforms = 2; break;
            case '3': std::cout << "Lifeforms = 3" << std::endl; ec.senses.numLifeforms = 3; break;
            case '4': std::cout << "Lifeforms = 4" << std::endl; ec.senses.numLifeforms = 4; break;

            }
        }
        ec.print();
        ec.poll();
        Sleep(100);
    }
    return 0;
}


//emotion is a feeling + impulse + expression
// pressuring the pet gives gives emotion of anxiety : the feeling of pressure and the impulse of stop/backup
// red = mad
// orange = scared
// yellow = joy
// green = powerful
// blue = peaceful
// purple = sad

//Actions that can change state
//  Anxiety = motion.backup 
//  Angry = lights.flash.red calms
//  Sad = motion.lookabout 
//  camera.found ... engagement++
//  camera.notfound .. engagement--

// Happy Engaged | Happy Bored
// Sad Engaged | Sad Bored
//27 unit boxes, need paper
