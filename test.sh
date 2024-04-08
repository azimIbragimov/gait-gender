rm -rf matrices/temp matrices/gaitgl/* matrices/gaitset/* matrices/gaitpart/*

cd /home/azim.usf/blue/azim.usf/1.Research/1.Gait/code/open_gait/july2023/OpenGait
mkdir matrices/temp
CUDA_VISIBLE_DEVICES=0,1,2,3 python -m torch.distributed.launch --nproc_per_node=4 opengait/main.py --cfgs configs/baseline/gaitgl_OUMVLP.yaml --phase test
mv matrices/temp/*.csv matrices/gaitgl/
CUDA_VISIBLE_DEVICES=0,1,2,3 python -m torch.distributed.launch --nproc_per_node=4 opengait/main.py --cfgs configs/gaitset/gaitset_OUMVLP.yaml --phase test
mv matrices/temp/*.csv matrices/gaitset/
CUDA_VISIBLE_DEVICES=0,1,2,3 python -m torch.distributed.launch --nproc_per_node=4 opengait/main.py --cfgs configs/gaitpart/gaitpart_OUMVLP.yaml --phase test
mv matrices/temp/*.csv matrices/gaitpart/
