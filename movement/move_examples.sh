go_home_helperL() {
    # This is with the arms over the table
    echo "ctpq time $1 off 0 pos (-12.0 24.0 23.0 64.0 -7.0 -5.0 10.0    12.0 -6.0 37.0 2.0 0.0 3.0 2.0 1.0 0.0)" | yarp rpc /ctpservice/left_arm/rpc
    # This is with the arms close to the legs
    # echo "ctpq time $1 off 0 pos (-6.0 23.0 25.0 29.0 -24.0 -3.0 -3.0 19.0 29.0 8.0 30.0 32.0 42.0 50.0 50.0 114.0)" | yarp rpc /ctpservice/left_arm/rpc
}

go_home_helperR() {
    # This is with the arms over the table
    echo "ctpq time $1 off 0 pos (-15.0 23.0 22.0 48.0 13.0 -10.0 8.0    0.0 9.0 42.0 2.0 0.0 1.0 0.0 8.0 4.0)" | yarp rpc /ctpservice/right_arm/rpc
    # This is with the arms close to the legs
    # echo "ctpq time $1 off 0 pos (-6.0 23.0 25.0 29.0 -24.0 -3.0 -3.0 19.0 29.0 8.0 30.0 32.0 42.0 50.0 50.0 114.0)" | yarp rpc /ctpservice/right_arm/rpc
}

go_home_helper() {
    go_home_helperR $1
    go_home_helperL $1
}

go_home() {
    ##breathers "stop"
    sleep 1.0
    go_home_helper 2.0
    sleep 3.0
    #breathers "start"
}

home_head() {
    echo "ctpq time 1.5 off 0 pos (0.0 0.0 0.0 0.0 0.0 0.0)" | yarp rpc /ctpservice/head/rpc
}

test_head() {
    echo "ctpq time 1.5 off 0 pos (0.0 0.0 -30.0 0.0 0.0 0.0)" | yarp rpc /ctpservice/head/rpc
    sleep 2.0
    echo "ctpq time 1.5 off 0 pos (0.0 0.0 30.0 0.0 0.0 0.0)" | yarp rpc /ctpservice/head/rpc
    sleep 2.0
    echo "ctpq time 1.5 off 0 pos (0.0 0.0 0.0 0.0 0.0 0.0)" | yarp rpc /ctpservice/head/rpc
}

hello_left() {
    echo "ctpq time 1.5 off 0 pos (-60.0 44.0 -2.0 96.0 53.0 -17.0 -11.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0)" | yarp rpc /ctpservice/left_arm/rpc
    sleep 2.0
    echo "ctpq time 0.5 off 0 pos (-60.0 44.0 -2.0 96.0 53.0 -17.0  25.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0)" | yarp rpc /ctpservice/left_arm/rpc
    echo "ctpq time 0.5 off 0 pos (-60.0 44.0 -2.0 96.0 53.0 -17.0 -11.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0)" | yarp rpc /ctpservice/left_arm/rpc
    echo "ctpq time 0.5 off 0 pos (-60.0 44.0 -2.0 96.0 53.0 -17.0  25.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0)" | yarp rpc /ctpservice/left_arm/rpc
    echo "ctpq time 0.5 off 0 pos (-60.0 44.0 -2.0 96.0 53.0 -17.0 -11.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0)" | yarp rpc /ctpservice/left_arm/rpc
    go_home 2.0
}
hello_right() {
    ##breathers "stop"
    echo "ctpq time 1.5 off 0 pos (-60.0 44.0 -2.0 96.0 53.0 -17.0 -11.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0)" | yarp rpc /ctpservice/right_arm/rpc
    sleep 2.0
    echo "ctpq time 0.5 off 0 pos (-60.0 44.0 -2.0 96.0 53.0 -17.0  25.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0)" | yarp rpc /ctpservice/right_arm/rpc
    echo "ctpq time 0.5 off 0 pos (-60.0 44.0 -2.0 96.0 53.0 -17.0 -11.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0)" | yarp rpc /ctpservice/right_arm/rpc
    echo "ctpq time 0.5 off 0 pos (-60.0 44.0 -2.0 96.0 53.0 -17.0  25.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0)" | yarp rpc /ctpservice/right_arm/rpc
    echo "ctpq time 0.5 off 0 pos (-60.0 44.0 -2.0 96.0 53.0 -17.0 -11.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0)" | yarp rpc /ctpservice/right_arm/rpc
    go_home
    #breathers "start"
}

look_left() {
    echo "ctpq time 1.5 off 0 pos (0.0 0.0 30.0 0.0 0.0 0.0)" | yarp rpc /ctpservice/head/rpc
}
look_right() {
    echo "ctpq time 1.5 off 0 pos (0.0 0.0 -30.0 0.0 0.0 0.0)" | yarp rpc /ctpservice/head/rpc
}

look_left() {
    echo "ctpq time 1.5 off 0 pos (0.0 0.0 30.0 0.0 0.0 0.0)" | yarp rpc /ctpservice/head/rpc
}

eyes_right() {
    echo "ctpq time 1.5 off 0 pos (0.0 0.0 0.0 0.0 20.0 0.0)" | yarp rpc /ctpservice/head/rpc
}

eyes_left() {
    echo "ctpq time 1.5 off 0 pos (0.0 0.0 0.0 0.0 -20.0 0.0)" | yarp rpc /ctpservice/head/rpc
}

sequence_01() {
    look_left
    sleep 1.0
    hello_left
    sleep 1.0
    look_right
    sleep 1.0
    hello_right
    sleep 1.0
    home_head
}

saccade() {
    eyes_left
    sleep 1.0
    eyes_right
    sleep 1.0
    home_head
}

sequence_02() {
    sequence_01
    sleep 1.0
    saccade
}

fix() {
    echo "ctpq time 1.5 off 0 pos (0.0 0.0 20.0 0.0 20.0 0.0)" | yarp rpc /ctpservice/head/rpc
}

echo "********************************************************************************"
echo ""

$1 "$2"

if [[ $# -eq 0 ]] ; then
    echo "No options were passed!"
    echo ""
    exit 1
fi