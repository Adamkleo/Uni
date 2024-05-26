const taskList = [];

const loadTasks = async () => {
  try {
      const response = await fetch("/tasks/get");
      if (!response.ok) {
          throw new Error('Network response was not ok');
      }
      const tasks = await response.json(); 
      taskList.splice(0, taskList.length, ...tasks); 
      displayTasks(); 
  } catch (error) {
      console.error('Error fetching tasks:', error);
  }
};


const add = () => {
  
  const input = document.getElementById('task-name');
  const taskTitle = input.value.trim();

  if (taskTitle) {
      
      const newTask = {
          id: taskList.length > 0 ? Math.max(...taskList.map(task => task.id)) + 1 : 1, 
          title: taskTitle,
          done: false
      };
      taskList.push(newTask);
      displayTasks();
      input.value = '';
	  saveTasks();
  } else {
      alert('Please enter a task name.');
  }
};


const remove = (taskId) => {
  const index = taskList.findIndex(task => task.id === taskId);
  if (index > -1) {
      taskList.splice(index, 1); 
      displayTasks(); 
	  saveTasks();
  }
};
const toggleDone = (taskId) => {
  
  const taskIndex = taskList.findIndex(task => task.id === taskId);
  if (taskIndex > -1) { 
      taskList[taskIndex].done = !taskList[taskIndex].done; 
      displayTasks();
	  saveTasks();
  }
};

const addButton = document.querySelector("#fab-add");
addButton.addEventListener('click', add); 
addButton.addEventListener("touchend", add);




const createGestureHandlers = (taskElement, taskId) => {
    let pressTimer;
    let fillEffect;
    let touchStartX = 0;
    let touchEndX = 0;
    let isLongPress = false; 

    const clearPressTimer = () => {
        clearTimeout(pressTimer);
        clearInterval(fillEffect);
        taskElement.classList.remove('filling', 'filled'); 
        taskElement.style.background = ''; 
        isLongPress = false; 
    };
	const startAction = (event) => {
		event.preventDefault();
		touchStartX = event.type === 'touchstart' ? event.changedTouches[0].screenX : event.screenX;
		touchEndX = 0;
		isLongPress = false;
	
		
		if (taskElement.classList.contains('task-completed')) {
			taskElement.classList.add('unfilling'); 
		} else {
			taskElement.classList.add('filling'); 
		}
	
		pressTimer = setTimeout(() => {
			isLongPress = true;
			if (taskElement.classList.contains('unfilling')) {
				taskElement.classList.remove('unfilling');
				
				toggleDone(taskId);
			} else if (taskElement.classList.contains('filling')) {
				taskElement.classList.remove('filling');
				
				toggleDone(taskId);
			}
			if (navigator.vibrate) {
				navigator.vibrate(50); 
			}
		}, 2000); 
	};
	
	

	const endAction = (event) => {
		touchEndX = event.type === 'touchend' ? event.changedTouches[0].screenX : event.screenX;
	
		if (touchStartX < touchEndX - 75) { 
			remove(taskId); 
			if (navigator.vibrate) {
				navigator.vibrate(50); 
			}
		} else if (isLongPress) { 
			
		}
	
		clearPressTimer();
	};
	
    taskElement.addEventListener('touchstart', startAction);
    taskElement.addEventListener('touchend', endAction);
    taskElement.addEventListener('mousedown', startAction);
    taskElement.addEventListener('mouseup', endAction);
    taskElement.addEventListener('mouseleave', clearPressTimer);
};




const displayTasks = () => {
  const taskContainer = document.getElementById('tasks');
  taskContainer.innerHTML = ''; 

  taskList.forEach(task => {
      const taskElement = document.createElement('li');
      taskElement.textContent = task.title;
      taskElement.setAttribute('data-id', task.id); 

      if (task.done) {
          taskElement.classList.add('task-completed');
      }

      createGestureHandlers(taskElement, task.id);
      taskContainer.appendChild(taskElement);
  });
};



  const saveTasks = async () => {

	try {
		await fetch("/tasklist/update", {
			method: 'POST',
			headers: {
				'Content-Type': 'application/json'
			},
			body: JSON.stringify(taskList, null, 4)
		});
		loadTasks();
	}
	catch (error) {
		console.log("Error al guardar las tareas.");
		console.log(error);
	}
}


document.addEventListener('DOMContentLoaded', loadTasks);


