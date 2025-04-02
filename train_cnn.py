#!/usr/bin/env python3
import tensorflow as tf
import os
from tensorflow.keras.preprocessing.image import ImageDataGenerator
from tensorflow.keras.applications.mobilenet_v2 import MobileNetV2, preprocess_input
from tensorflow.keras.layers import GlobalAveragePooling2D, Dense, Dropout
from tensorflow.keras.models import Sequential
from tensorflow.keras.optimizers import Adam
from tensorflow.keras.callbacks import EarlyStopping

def train_two_phase_finetuning(data_dir, batch_size=8, img_size=(224,224), epochs1=5, epochs2=5):
    """
    Example code for a two-phase fine-tuning approach.
    1) Phase 1: Freeze partial network from layer 0..fine_tune_at, train at LR=1e-4
    2) Phase 2: Unfreeze more layers (or all), reduce LR to e.g. 1e-5, train more.
    """

    train_datagen = ImageDataGenerator(
        preprocessing_function=preprocess_input,
        validation_split=0.2
    )

    train_generator = train_datagen.flow_from_directory(
        data_dir,
        target_size=img_size,
        batch_size=batch_size,
        class_mode='categorical',
        subset='training'
    )

    val_generator = train_datagen.flow_from_directory(
        data_dir,
        target_size=img_size,
        batch_size=batch_size,
        class_mode='categorical',
        subset='validation'
    )

    base_model = MobileNetV2(weights='imagenet', include_top=False,
                             input_shape=(img_size[0], img_size[1], 3))

    # Phase 1: Partial freeze
    fine_tune_at = 100
    for layer in base_model.layers[:fine_tune_at]:
        layer.trainable = False
    for layer in base_model.layers[fine_tune_at:]:
        layer.trainable = True

    # Build the top model
    model = Sequential([
        base_model,
        GlobalAveragePooling2D(),
        # Dropout 
        Dropout(0.3),
        Dense(128, activation='relu'),
        Dense(train_generator.num_classes, activation='softmax')
    ])

    # Phase 1 compile: LR=1e-4
    optimizer = Adam(learning_rate=1e-4)
    model.compile(
        optimizer=optimizer,
        loss='categorical_crossentropy',
        metrics=['accuracy']
    )

    early_stop = EarlyStopping(monitor='val_loss', patience=3, restore_best_weights=True)

    print("------ Phase 1 training ------")
    model.fit(
        train_generator,
        epochs=epochs1,
        validation_data=val_generator,
        callbacks=[early_stop]
    )

    # Phase 2: Unfreeze more (or all) + lower LR
    base_model.trainable = True
    # Optional: unfreeze from layer 80, or 0 for all. Example:
    # for layer in base_model.layers[:80]:
    #     layer.trainable = False

    model.compile(
        optimizer=Adam(learning_rate=1e-5),  # smaller LR
        loss='categorical_crossentropy',
        metrics=['accuracy']
    )

    print("------ Phase 2 fine-tuning ------")
    model.fit(
        train_generator,
        epochs=epochs2,
        validation_data=val_generator,
        callbacks=[early_stop]
    )

    model.save("solder_classifier_two_phase.keras")
    print("Saved two-phase model -> 'solder_classifier_two_phase.keras'")

def main():
    data_dir = "labeled_data"
    train_two_phase_finetuning(
        data_dir,
        batch_size=8,
        img_size=(224,224),
        epochs1=5,   # e.g. 5 epochs for phase 1
        epochs2=5    # e.g. 5 epochs for phase 2
    )

if __name__ == "__main__":
    main()
