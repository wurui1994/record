const { Worker, isMainThread, parentPort, workerData } = require(
  "node:worker_threads",
);

if (isMainThread) {
  for (let i = 0; i < 4; i++) {
    const worker = new Worker(__filename, {
      workerData: "worker_" + i.toString(),
    });
    worker.once("message", (message) => {
      console.log("Parent recv", message); // Prints 'Hello, world!'.
    });
    worker.postMessage("Hello, world!" + worker.threadId.toString());
  }
} else {
  // When a message from the parent thread is received, send it back:
  console.log(workerData);
  parentPort.once("message", (message) => {
    parentPort.postMessage(message);
    console.log("Child recv:", message);
  });
  // while (1);
}
