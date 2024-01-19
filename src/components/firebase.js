import { initializeApp } from 'firebase/app';
import { getDatabase, ref, push } from 'firebase/database';

const firebaseConfig ={
  apiKey: "AIzaSyABXTpgXJhHMPcv9E5jb8VYCoGFzjvX3Rg",
  authDomain: "clawmachine-37996.firebaseapp.com",
  projectId: "clawmachine-37996",
  storageBucket: "clawmachine-37996.appspot.com",
  databaseURL: "https://clawmachine-37996-default-rtdb.europe-west1.firebasedatabase.app/",
  messagingSenderId: "146135088061",
  appId: "1:146135088061:web:f6517dbc45e08b5130b0d4",
};

const firebaseApp = initializeApp(firebaseConfig);
const db = getDatabase(firebaseApp);

export { db, ref, push };