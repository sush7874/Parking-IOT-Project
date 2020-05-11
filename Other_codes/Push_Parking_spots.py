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
#creating 10 slots
#data = {'slot1':'0','slot2': '0', 'slot3':'0','slot4':'0','slot5':'0','slot6':'0','slot7':'0','slot8':'0','slot9':'0','slot10':'0'}
#db.child("slots").set(data)
dict1 = {1:'slot1', 2:'slot2', 3:'slot3', 4:'slot4', 5:'slot5', 6:'slot6', 7:'slot7', 8:'slot8', 9:'slot9', 10:'slot10'}
for i in range(1,15):
    x = random.randint(1,10)
    slot_name = dict1[x]
    val = db.child("slots").child(slot_name).child('available').get().val()
    if(val==0):
        #update to occupied
        db.child("slots").child(slot_name).update({'available' : 1})
        print("Slot ",x, "occupied ")
        print(db.child("slots").child(slot_name).child('available').get().val())
    if(val==1):
        db.child("slots").child(slot_name).update({'available': 0})
        print("Slot ",x ," empty")
        print(db.child("slots").child(slot_name).child('available').get().val())
