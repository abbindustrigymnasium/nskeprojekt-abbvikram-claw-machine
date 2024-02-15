<template>
    <div class="grid">
      <div v-for="row in 3" :key="row" class="row">
        <div
          v-for="col in 4"
          :key="`${row}-${col}`"
          :class="['square', { 'lit-up': isLitUp(`${row}-${col}`) }]"
          @click="lightUpSquare(`${row}-${col}`)"
        ></div>
      </div>
    </div>
  </template>
  
  <script>
  import { db, set, ref } from '@/components/firebase'; // Adjust the path to your Firebase configuration
  
  export default {
    data() {
      return {
        litSquares: {}, // Object to track lit-up state with timeouts
      };
    },
    methods: {
      lightUpSquare(squareId) {
        // Light up the square
        this.$set(this.litSquares, squareId, true);
  
        // Extract the row and column from squareId
        const [row, col] = squareId.split('-').map(Number);
  
        // Adjust Y to correct the inversion
        const totalRows = 3;
        const adjustedRow = totalRows + 1 - row;
  
        // Send the row and column as X and Y to Firebase, correctly mapping Y
        set(ref(db, 'clickedSquares'), {
          X: col,
          Y: adjustedRow,
        });
  
        // Set a timeout to un-light it after 1 second
        setTimeout(() => {
          this.$delete(this.litSquares, squareId);
        }, 1000); // 1000 milliseconds = 1 second
      },
      isLitUp(squareId) {
        return !!this.litSquares[squareId];
      },
    },
  };
  </script>
  
  <style>
  .grid {
    display: flex;
    flex-direction: column;
    user-select: none;
  }
  .row {
    display: flex;
  }
  .square {
    width: 100px;
    height: 100px;
    border: 1px solid #ffffff;
    margin: -1px;
    cursor: pointer;
    background-color: #000; /* Default background color */
    transition: background-color 1s ease-out; /* Smooth transition for fading effect */
  }
  .lit-up {
    background-color: #fff; /* White color when lit up */
    animation: fadeAway 1s ease-out forwards; /* Animation to fade away */
  }
  
  @keyframes fadeAway {
    from {
      background-color: #fff;
    }
    to {
      background-color: #000;
    }
  }
  </style>
  