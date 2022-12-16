#include <conio.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

//tinymega ultrasound https://andrewjkramer.net/tag/sonar/

    /*
    Happy Engaged Unsure = inquisitive
    Happy Engaged Balanced = playful
    Happy Engaged Confident = motivated
    Happy Balanced Unsure = waiting
    Happy Balanced Balanced = happy
    Happy Balanced Confident = proud
    Happy Detached Unsure = shy
    Happy Detached Balanced = calm
    Happy Detached Confident = nice
    Balanced Engaged Unsure = hesitant
    Balanced Engaged Balanced = engaged
    Balanced Engaged Confident = decisive
    Balanced Balanced Unsure = unsure
    Balanced Balanced Balanced = centered
    Balanced Balanced Confident = focused
    Balanced Detached Unsure = shy
    Balanced Detached Balanced = detached
    Balanced Detached Confident = skeptical        
    Sad Engaged Unsure = wary
    Sad Engaged Balanced = mopey
    Sad Engaged Confident = aggressive
    Sad Balanced Unsure = uncomfortable
    Sad Balanced Balanced = sad
    Sad Balanced Confident = resigned
    Sad Detached Unsure = lost
    Sad Detached Balanced = lonely
    Sad Detached Confident = alone
    */
class Emotion
{
public:
    std::string feeling;
    std::string impulse;
    std::string expression;
    float freedom;
    float positivity;
    float engagement;
    Emotion(float f, float p, float e, std::string sf, std::string si, std::string se)
    {
        feeling = sf;
        impulse = si;
        expression = se;
        freedom = f;
        positivity = p;
        engagement = e;
    }
};

#define LO 0.3333
#define HI 0.6666
#define MX 1.0000

std::vector<Emotion> emotions
{
    Emotion(LO,LO,LO, "distressed",     "retreat",  "glow red,say whimper,motion retreat"),
    Emotion(HI,LO,LO, "lonely",         "whimper",  "glow yellow,say whimper,pose wait"),
    Emotion(MX,LO,LO, "alone",          "search",   "glow blue,say hunt,motion search"),
    Emotion(LO,LO,HI, "aggressive",     "growl",    "glow red,say growl,pose fight"),
    Emotion(HI,LO,HI, "sad",            "paw",      "glow yellow,say mrewl,motion pawshake"),
    Emotion(MX,LO,HI, "resigned",       "stare",    "glow blue,say nothing,pose wait"),
    Emotion(LO,LO,MX, "uncomfortable",  "wait",     "glow red,say hmewl,pose wait"),
    Emotion(HI,LO,MX, "mopey",          "mope",     "glow yellow,say nothing,pose wait"),
    Emotion(MX,LO,MX, "interested",     "watch",    "glow blue,say nothing,pose wait"),

    Emotion(LO,HI,LO, "shy",            "cower",    ""),
    Emotion(HI,HI,LO, "detached",       "search",   ""),
    Emotion(MX,HI,LO, "skeptical",      "search",   ""),
    Emotion(LO,HI,HI, "unsure",         "whine",    ""),
    Emotion(HI,HI,HI, "centered",       "nothing",  ""),
    Emotion(MX,HI,HI, "focused",        "continue", ""),
    Emotion(LO,HI,MX, "hesitant",       "wait",     ""), 
    Emotion(HI,HI,MX, "engaged",        "be",       ""),
    Emotion(MX,HI,MX, "decisive",       "be",       ""),

    Emotion(LO,MX,LO, "shy",            "mewl",     ""),
    Emotion(HI,MX,LO, "calm",           "mew",      ""),
    Emotion(MX,MX,LO, "nice",           "sing",     ""),
    Emotion(LO,MX,HI, "waiting",        "wait",     ""),
    Emotion(HI,MX,HI, "happy",          "be",       ""),
    Emotion(MX,MX,HI, "proud",          "be",       ""),
    Emotion(LO,MX,MX, "curious",        "wait",     ""),
    Emotion(HI,MX,MX, "playful",        "play",     ""),
    Emotion(MX,MX,MX, "ecstastic",      "be",       ""),
};


const Emotion FeelingToName(float freedom, float positivity, float engagement)
{
    for (int i = 0; i < emotions.size(); i++)
    {
        Emotion& e = emotions[i];
        if (freedom <= e.freedom && positivity <= e.positivity && engagement <= e.engagement)        
            return e;
    }
    return Emotion(0, 0, 0, "unknown", "unk", "");
}

class EmotionalPoint
{
public:
    float Confidence = 0; //Confidence
    float Positivity = 0; //Positivity
    float Engagement = 0; //Engagement
    float dirX = 0;
    float dirY = 0;
    float dirZ = 0;
    float spanX = 0;
    float spanY = 0;
    float spanZ = 0;
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


public:
    EmotionalPoint()
    {
        this->Confidence = 0.5f;
        this->Positivity = 0.5f;
        this->Engagement = 0.5f;
    }
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
        basis = EmotionalPoint(bx, by, bz);
        current = EmotionalPoint(0.5f, 0.5f, 0.5f);
    }
    void print()
    {
        Emotion emotion = FeelingToName(current.Confidence, current.Positivity, current.Engagement);
        std::cout << std::to_string(senses.tick)
            << "] " 
            << "Confidence=" << std::to_string((int)(current.Confidence * 100)) << "%, "
            << "Positivity=" << std::to_string((int)(current.Positivity * 100)) << "%, "
            << "Engagement=" << std::to_string((int)(current.Engagement * 100)) << "%  "
            << "= " << emotion.feeling
            << ", " << emotion.impulse
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

