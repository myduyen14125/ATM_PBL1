from fastapi import FastAPI, Query, Request
from fastapi.responses import JSONResponse
from PIL import Image
from tensorflow.keras.utils import load_img, img_to_array
from keras.models import load_model
import requests
from IPython.display import Image
import numpy as np
import tensorflow as tf
from pydantic import BaseModel
import time
# from tensorflow.python.layers.normalization import BatchNormalization

# Define image classification classes (replace with your actual classes)
CLASSES = ['gambling', 'hentai', 'safe', 'sexy', 'violence', 'weapon']

app = FastAPI()
model_path = "models/mobilenet_nfsw.h5"

class ImageURL(BaseModel):
    image_url: str

# Function to preprocess the image (resize, normalize)
def preprocess_image(image_path, target_size=(224, 224)):
    print("Preprocessing image")
    img = load_img(image_path, target_size=target_size)
    x = img_to_array(img)
    x = np.expand_dims(x, axis=0)
    return x

def predict_image(image_array, model_path):
    try:
        model = load_model(model_path, compile=False)
        predictions = model.predict(image_array)
        print(predictions)
        predicted_class = np.argmax(predictions)
        predicted_label = CLASSES[predicted_class]

        return predicted_label
    except Exception as e:
        print(f"Error making prediction: {e}")
        return "Error: Could not predict class"

# FastAPI endpoint for image classification
@app.post("/predict")
async def predict_image_from_url(request: Request, payload: ImageURL):
    image_url = payload.image_url
    try:
        print(f"Predicting image from URL: {image_url}")
        
        # Download image from URL using requests
        response = requests.get(image_url)
        image_name = 'real.png'
        with open(image_name, "wb") as f:
            f.write(response.content)
        
        image = Image(image_name, width=200)
        image_name = 'real.png'
        image = preprocess_image(image_name)
        
        # Measure prediction time
        start_time = time.time()
        predicted_class = predict_image(image, model_path)
        end_time = time.time()
        
        prediction_time = end_time - start_time
        
        return {
            "predicted_class": predicted_class,
            "prediction_time": prediction_time
        }
    except Exception as e:
        return JSONResponse(status_code=500, content={"message": str(e)})
        
    # except Exception as e:
    #     print(f"Error during prediction: {e}")
    #     return {"error": "Internal server error"}

# Endpoint for testing purposes (can be removed in production)
@app.get("/")
async def root():
    return {"message": "FastAPI Image Classification Server is ready!"}

# Run the server (adjust host and port as needed)
if __name__ == "__main__":
    import uvicorn
    # print version tensorflow
    uvicorn.run("main:app", host="0.0.0.0", port=8000)  # Replace with desired host and port
