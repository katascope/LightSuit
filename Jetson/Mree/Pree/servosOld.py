SFrontLeftHip = 4
SFrontLeftArm = 5
SFrontLeftWrist = 6
SFrontRightHip = 8
SFrontRightArm = 9
SFrontRightWrist = 10
SBackLeftHip = 0
SBackLeftArm = 1
SBackLeftWrist = 2
SBackRightHip = 12
SBackRightArm = 13
SBackRightWrist = 14

#ServoHips = [SFrontLeftHip, SFrontRightHip, SBackLeftHip, SBackRightHip]
#ervoHips = [SFrontLeftHip]
ServoAll = [
        SFrontLeftWrist,
        SFrontLeftArm,
        SFrontLeftHip,

        SFrontRightWrist,
        SFrontRightArm,
        SFrontRightHip,
        
        SBackLeftWrist,
        SBackLeftArm,
        SBackLeftHip,

        SBackRightWrist,
        SBackRightArm,
        SBackRightHip
        ]

ServoWrists = [SFrontLeftWrist, SBackLeftWrist]

#wrists 40 to 180 #Wrists 'center' at 150
#hips 30 to 140 #hips 'center' at ?

def fu():
    print('fuTest')

def about():
    print('about')

print('Servos Module OK')
