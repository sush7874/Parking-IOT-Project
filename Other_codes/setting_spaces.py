import pyrebase
import random
config = {
  "apiKey": "AIzaSyD2euzMxNvGE3zg0uUuhKhIJZDHRADB-4w",
  "authDomain": "iot-proj-bcf82.firebaseapp.com",
  "databaseURL": "https://iot-proj-bcf82.firebaseio.com/",
  "storageBucket": "iot-proj-bcf82.appspot.com",
  "serviceAccount": "iot-proj-bcf82-firebase-adminsdk-541k9-213d7067ce.json"
}


firebase = pyrebase.initialize_app(config)
auth = firebase.auth()

# Log the user in
user = auth.sign_in_with_email_and_password("me@gmail.com", "password")
db = firebase.database()
slot1 = {'available' : 0, 'x': 500, 'y':300}
slot2 = {'available' : 0, 'x': 500, 'y':400}
slot3 = {'available' : 0, 'x': 500, 'y':500}
slot4 = {'available' : 0, 'x': 500, 'y':600}
slot5 = {'available' : 0, 'x': 500, 'y':700}
slot6 = {'available' : 0, 'x': 800, 'y':300}
slot7 = {'available' : 0, 'x': 800, 'y':400}
slot8 = {'available' : 0, 'x': 800, 'y':500}
slot9 = {'available' : 0, 'x': 800, 'y':600}
slot10 = {'available' : 0, 'x': 800, 'y':700}
db.child("slots").child("slot1").set(slot1)
db.child("slots").child("slot2").set(slot2)
db.child("slots").child("slot3").set(slot3)
db.child("slots").child("slot4").set(slot4)
db.child("slots").child("slot5").set(slot5)
db.child("slots").child("slot6").set(slot6)
db.child("slots").child("slot7").set(slot7)
db.child("slots").child("slot8").set(slot8)
db.child("slots").child("slot9").set(slot9)
db.child("slots").child("slot10").set(slot10)
