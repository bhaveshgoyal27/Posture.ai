<p align="center">
  <img src="https://github.com/Shobhit2000/Posture.ai/blob/master/Dump/Frame%2013.png" width="1000" title="hover text">
</p>

## Inspiration
With more people working at home due to the pandemic, we felt empowered to improve healthcare at an individual level. Existing solutions for posture detection are expensive, lack cross-platform support, and often require additional device purchases. We sought to remedy these issues by creating posture.AI.

## What it does
Posture.AI uses your laptop's camera to analyze and help you improve your posture. Register and calibrate the system in less than two minutes, and simply keep the application open in the background and continue working. posture.AI will notify you if you begin to slouch so you can correct it.

Some notable features include:

Smart slouch detection with ML Works even when a person is not sitting in front of the camera as we have provided biscuit-sized hardware that can be placed on the back and tracks your body movements. 
Little overhead - get started in < 2 min Native notifications on any platform

## How we built it
We created posture.AI's desktop app using Electron.js, an npm package used to develop cross-platform apps. We created the individual pages for the app using HTML, CSS, and client-side JavaScript. For the onboarding screens, users fill out an HTML form that signs them in using Firebase Authentication and uploads information such as their name and preferences to Firestore. This data is also persisted locally using NeDB, a local JavaScript database. The menu bar addition incorporates a camera through a MediaDevices web API, which gives us frames of the user’s posture. Using Tensorflow’s PoseNet model, we analyzed these frames to determine if the user is slouching and if so, by how much. The app sends a desktop notification to alert the user about their posture and also uploads this data to Firestore. The hardware version is developed using NodeMCU and MPU6050 and connected to the same backend database to the firebase realtime database which alerts the user regarding their posture even when the person is not sitting in front of the camera.

## Challenges we ran into
As this was our first time using Electron, our team spent a lot of time discovering ways to pass data safely and efficiently, discussing the pros and cons of different solutions. Another significant challenge was performing machine learning on the video frames. The task of taking in a stream of camera frames and outputting them into slouching percentage values was quite demanding, but we were able to overcome several bugs and obstacles along the way to create the final product.

## Accomplishments that we're proud of
We’re proud that we’ve come up with a seamless and beautiful design that takes less than a minute to setup. The slouch detection model is also pretty accurate, something that we’re pretty proud of. The wireless hardware module is also working as expected and gives amazing results. Overall, we’ve built a robust system that we believe outperforms other solutions using just the web camera of your computer when sitting in front of the system and also even when the person is not sitting in front of the system, while also integrating features to track slouching data on the user's device.

## What we learned
This project taught us how to combine multiple complicated moving pieces into one application. Specifically, we learned how to make a native desktop application with features like notifications built-in using Electron. We also learned how to connect our backend posture data with Firestore to relay information from our Electron application to the user's local system and simultaneously working hardware even when people are not sitting in front of the system. Lastly, we learned how to integrate a machine learning model in Tensorflow within our Electron application.

## What's next for Upright
The next step is improving the posture detection model with more training data, tailored for each user. While the posture detection model we currently use is pretty accurate, by using more custom-tailored training data, it would take Upright to the next level. Another step for Upright would be adding Android integration for our mobile app, which currently only supports desktop now.
