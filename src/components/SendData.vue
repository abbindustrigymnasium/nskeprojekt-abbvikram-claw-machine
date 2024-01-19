<template>
    <div>
      <form @submit.prevent="submitData">
        <label for="dataInput">Data:</label>
        <input v-model="data" type="text" id="dataInput" />
        <button type="submit">Submit</button>
      </form>
  
      <!-- Button to send the number 1 -->
      <button @click="sendNumber">Send Number 1</button>
    </div>
  </template>
  
  <script>
  import { db, push, ref } from '@/components/firebase'; // Adjust the path accordingly
  
  export default {
    data() {
      return {
        data: '',
      };
    },
    methods: {
      submitData() {
        // Push data to the database
        push(ref(db, 'your_data_path'), {
          data: this.data,
        });
  
        // Clear the input field after submission
        this.data = '';
      },
      sendNumber() {
        // Push the number 1 to the database
        push(ref(db, 'your_data_path'), {
          data: 1,
        });
      },
    },
  };
  </script>