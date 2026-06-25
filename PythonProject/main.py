# This is a sample Python script.
import json
import threading
import time
import urllib

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.
import cv2
import http
import os
from os.path import isfile, join

import requests
from urllib3.util import wait

base_since_reset: float|int = 0
sum = 0
isrunning = True

values = [
    # CS-world
    {"total": 20,
        "phases":[
            # bug appearing
        {"range":  [0,30],
         "cont": True,#does update or plays through
         "loops": False,
         "threshold":0,
         "color":(255,255,255)
         },
            #bug crawling/disappearing
        {
            "threshold": 0.1,
            "range": [31, 46],
            "cont": False,  # does update or plays through
            "loops": False,
            "color": (255, 255, 255)

        },
            #fill bar
        {     "threshold": 0.3,
            "range": [47, 99],
            "cont": False,  # does update or plays through
            "loops": False,
              "color": (255, 255, 255)
              },
            #final portal
{     "threshold": 1,
            "range": [100, 191],
            "cont": True,  # does update or plays through
            "loops": False,
      "color": (255, 255, 255)
      }
]},
    #chemistry
    {"total": 10,
        "phases":[
       #begin
        {"range":  [0,33],
         "cont": True,
         "loops": False,
         "threshold":0,
         "color":(0,0,200)},
       #grow skull

       #skull loop
        {"range": [34, 64],
        "cont": True,
        "loops": True,
        "threshold": 0,
         "color":(0,0,200)
         },
       #fill blue
        {"range": [65, 128],
        "cont": False,
        "loops": False,
        "threshold": 0.4,
            "color":(0, 100, 200)}

,
       #bike
       {"range": [129, 169],
        "cont": True,
        "loops": True,
        "threshold": 0.8,
        "color": ( 0,200,200)
        },
       #portal
       {"range": [170, 192],
        "cont": True,
        "loops": False,
        "threshold": 1,
        "color": (0,200, 100)
        },
]},
    # architecture
    {"total": 20,
        "phases":[
        {"range":  [0,104],
         "cont": False,
         "loops": False,
         "threshold": 0,
         "color": (0, 200, 220)}
         ,
        {
"range":  [105,192],
         "cont": True,
         "loops": False,
         "threshold": 1.0,
"color": (0, 200, 220)
        },

]}
]
def change_video(cap, path):
    cap.release()
    return cv2.VideoCapture(path)


def  calculate_ratio(c:float|int,total:float|int):
    return min((sum-base_since_reset+c)/total,1)


def request(url):
    while isrunning:
        global sum
        x = requests.get(url)
        v =json.loads(x.content)

        #globals()["sum"]  =v['sum']
        print("in request", sum)
        time.sleep(3)

def play_video(folder, url):
    # load video capture from file
    global isrunning
    global sum
    global base_since_reset

    video_list = []
    t = threading.Thread(target=request, args=(url,))
    t.start()

    onlyfiles = [f for f in os.listdir(folder) if isfile(join(folder, f))]
    for path in onlyfiles:
        if not path.endswith(".mp4"):
            continue

        #print(path)
        video = cv2.VideoCapture(os.path.join(folder, path))
        frames = video.get(cv2.CAP_PROP_FRAME_COUNT)
        video_list.append((path, frames))
        video.release()
    total = len(video_list)
    font = cv2.FONT_HERSHEY_SIMPLEX
    #3 architecture
    bottomLeftCornerOfText = (32, 55)
    fontScale = 1
    fontColor = (255, 255, 255)
    thickness = 1
    lineType = 2

    i =0
    index =0
    elapsed =0
    finished_phase= False
    p, frame_amount = video_list[index]
    current_context = values[index]
    phase  = current_context["phases"][0]
    allphases=len(current_context["phases"])
    colour = phase["color"]
    range = phase["range"]

    total_km = current_context["total"]

    phaseno=0
    nextphase  =  None
    controlled =0
    prevratio=0

    if phaseno<allphases:
        nextphase = current_context["phases"][1]

    # window name and size
    cv2.namedWindow('TUrn green', flags=cv2.WINDOW_GUI_NORMAL)
    cv2.resizeWindow('TUrn green', 1280, 720)

    video = cv2.VideoCapture(os.path.join(folder, p))

    base_since_reset=sum
    while isrunning:



        #status =
        ratio = calculate_ratio(controlled,total_km)

        if phase["cont"]:
            if not finished_phase or phase["loops"] :
                status = (i%((range[1]-range[0])+1))+elapsed
            if finished_phase and not phase["loops"]:
                status=range[1]

        else:
            if nextphase:
                rdiff = nextphase["threshold"] - phase["threshold"]
                diff = ratio -phase["threshold"]
                if not rdiff==0:
                    diff /=rdiff

                status = (diff*(range[1]-range[0]+1))+elapsed
        if ((status+1) > range[1]):
            finished_phase = True
        video.set(cv2.CAP_PROP_POS_FRAMES, min(status,frame_amount-1))
        #print("frame", min(status,frame_amount-1), finished_phase)
        ret, frame = video.read()


        # Read video capturel

        x,y = bottomLeftCornerOfText
        corner = (x, y+20)

        # Display each frame
        cv2.rectangle(frame, (5, 10), (300, 150), 0, -1)

        cv2.putText(frame, f"{round(ratio*total_km,2)}/{total_km} km",
                    bottomLeftCornerOfText,
                    font,
                    fontScale,
                    colour,
                    thickness,
                    lineType)
        cv2.putText(frame, "FACULTY PROGRESS",
                    corner,
                    font,
                    0.5*fontScale,
                    colour,
                    thickness,
                    lineType)
        #30+250*ratio
        new_dims =(int(30+(ratio*250)), 120)
        cv2.rectangle(frame, (30, 100), (280, 120), colour, 1)
        cv2.rectangle(frame, (30, 100), new_dims, colour, -1)

        cv2.imshow("TUrn green", frame)
        # show one frame at a time
        # Quit when 'q' is pressed
        key = cv2.waitKey(1)
        if key == ord('q'):
            isrunning = False
        elif key == ord('l'):
            controlled+=0.1
            if controlled >=frame_amount:
                controlled = frame_amount-1
        elif key == ord('k'):
            controlled -= 0.1
            if controlled<0:
                controlled=0
        elif key == ord('a'):
            index = index-1
            if index < 0:
                index += total
            p, frame_amount = video_list[index]
            current_context = values[index]
            phase = current_context["phases"][0]
            print(phase)

            colour = phase["color"]
            total_km = current_context["total"]
            base_since_reset = sum
            range = phase["range"]
            elapsed = 0
            allphases = len(current_context["phases"])

            phaseno=0

            if phaseno < allphases:
                nextphase = current_context["phases"][1]
            video=change_video(video, os.path.join(folder, p))
        elif key == ord('d'):
            index = index+1
            if index >= total:
                index -= total
            p, frame_amount = video_list[index]
            current_context = values[index]
            phase = current_context["phases"][0]
            base_since_reset = sum
            phaseno=0
            colour = phase["color"]
            range = phase["range"]
            elapsed =0
            total_km = current_context["total"]
            video=change_video(video, os.path.join(folder, p))
            allphases = len(current_context["phases"])

            if phaseno < allphases:
                nextphase = current_context["phases"][1]

            base_since_reset = sum

        elif key == ord('r'):
            base_since_reset = sum
            controlled=0
            phase = current_context["phases"][0]
            print(phase)

            colour = phase["color"]
            total_km = current_context["total"]
            base_since_reset = sum
            range = phase["range"]
            elapsed = 0
            allphases = len(current_context["phases"])
            if phaseno < allphases:
                nextphase = current_context["phases"][1]
            video = change_video(video, os.path.join(folder, p))

        i += 1
        i = min(i, frame_amount)
        if nextphase == None:
            if finished_phase:
                ...
            continue
        if ratio >= nextphase["threshold"] and finished_phase:

            prevratio = phase["threshold"]
            phase = nextphase
            colour = phase["color"]
            range = phase["range"]
            elapsed = range[0]
            #print(elapsed)
            finished_phase=False
            i=0
            phaseno += 1

            if (phaseno +1) < allphases:
                nextphase = current_context["phases"][phaseno+1]

            else:
                nextphase = None
            #print(phase, nextphase)

    # Release capture object
    video.release()
    # Exit and distroy all windows
    cv2.destroyAllWindows()

if __name__ == '__main__':
    #play_video("/home/anna/Downloads/Visualizations Final/", "http://172.2.10.4:5000/distance")
    play_video("/home/anna/Downloads/Visualizations Final/", "http://localhost:5000/distance")

