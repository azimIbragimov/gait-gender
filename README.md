# Instructions on how to run our code

## Ensure that you have the following dependecies
- pytorch >= 1.10
- torchvision
- pyyaml
- tensorboard
- opencv-python
- tqdm
- py7zr
- kornia
- Latest version of C++. 

## Clone OpenGait repository
```
$ git clone https://github.com/ShiqiYu/OpenGait.git
```
Ensure that OpenGait and its dependecies are installed correctly. 

## Dataset
Follow through OpenGait preprocessing instructions for the OU-MVLP dataset and place the .pkl file in the `./data` folder. 

```
$ mv PATH_TO_PKL_FILE ./data/OUMVLP.pkl
```

# OpenGait modifications
Apply our modifications to OpenGait to enable gender analysis:
```
$ bash ./src/move_files.sh
```

# Run the evaluation script
This script will create the score matrices required for gender analysis:
```
bash ./OpenGait/test.sh
```


# Experiments
To replicate the results discussed in the paper, run the following commands:

```
jupyter nbconvert --execute src/split.ipynb --to html   # generate random strata

bash ./src/experiment.sh                                # compute genuine/impostor distributions

jupyter nbconvert --execute src/plot.ipynb --to html    # plot the results
```

This will create a file `plot.html` with the results in the same format as presented in the paper (histograms, ROC curves, heatmaps, and $d_B$+$EER$ values).

# Citations
Please cite our work, as well as OpenGait. 

```
@InProceedings{Ibragimov_2024_FG,
    author    = {Ibragimov, Azim and Pamplona Segundo, Mauricio and Sarkar, Sudeep and Bowyer, Kevin},
    title     = {Unveiling Gender Effects in Gait Recognition using Conditional-Matched Bootstrap Analysis},
    month     = {May},
    year      = {2024},
}
```

```
@InProceedings{Fan_2023_CVPR,
    author    = {Fan, Chao and Liang, Junhao and Shen, Chuanfu and Hou, Saihui and Huang, Yongzhen and Yu, Shiqi},
    title     = {OpenGait: Revisiting Gait Recognition Towards Better Practicality},
    booktitle = {Proceedings of the IEEE/CVF Conference on Computer Vision and Pattern Recognition (CVPR)},
    month     = {June},
    year      = {2023},
    pages     = {9707-9716}
}
```
