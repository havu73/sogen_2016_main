/*
Simulation for zebrafish segmentation
Copyright (C) 2013 Ahmet Ay, Jack Holland, Adriana Sperlea, Sebastian Sangervasi

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
tests.cpp contains test functions for every mutant.
*/

#include "tests.hpp" // Function declarations
#include "macros.hpp"


/*
 *  To see how each of the features is calculated in the test, refer to featues.cpp
 *  To see which tests are important, refer to init.cpp
 */




double test_wildtype_post (mutant_data& md, features& wtfeat) {
    md.conds_passed[SEC_POST][0] = 28 < md.feat.period_post && md.feat.period_post < 32;  // ***29 30
    md.conds_passed[SEC_POST][1] = md.feat.peaktotrough_end >= 1.5 && md.feat.peaktotrough_mid >= 1.5 && (md.feat.peaktotrough_mid / md.feat.peaktotrough_end) <= 1.5;
    cout<<"WILD P0: "<<md.conds_passed[SEC_POST][0]*5<<endl;
    cout<<"WILD P1: "<<md.conds_passed[SEC_POST][1]*5<<endl;
    
    //print total socre for this mutant
    cout<<"WILD POST SUM "<<(md.conds_passed[SEC_POST][1] * md.cond_scores[SEC_POST][1]) +
    (md.conds_passed[SEC_POST][0] * md.cond_scores[SEC_POST][0])<<endl;
    
    return  (md.conds_passed[SEC_POST][1] * md.cond_scores[SEC_POST][1]) +
            (md.conds_passed[SEC_POST][0] * md.cond_scores[SEC_POST][0]);
    

}


double test_wildtype_ant (mutant_data& md, features& wtfeat) {
    // 1.4-2.2 period ratio of ant/post, should be condition2, details in feats.cpp
    cout<<"WILD 0: "<<md.conds_passed[SEC_ANT][0]*5<<endl;
    
    //wild 1
    md.conds_passed[SEC_ANT][1] = md.feat.sync_score_ant[IMH1] > 0.8;
    //print score
    cout<<"WILD 1: "<<md.conds_passed[SEC_ANT][1]*5<<"; "<< md.feat.sync_score_ant[IMH1]<<endl;
    
    //complementary conditions - two measures
    md.conds_passed[SEC_ANT][4] = (md.feat.comp_score_ant_mespa<= -0.7 && md.feat.comp_score_ant_mespa>= -1) ? 1 : (1 - (md.feat.comp_score_ant_mespa + .7));
    md.conds_passed[SEC_ANT][5] = (md.feat.comp_score_ant_mespb<= -0.7 && md.feat.comp_score_ant_mespb>= -1) ? 1 : (1 - (md.feat.comp_score_ant_mespb + .7));
    md.conds_passed[SEC_ANT][6] = (md.feat.sync_score_ant[1] <= -0.7 && md.feat.sync_score_ant[1]>= -1) ? 1 : (1 - (md.feat.sync_score_ant[1] +.7 ));
    md.conds_passed[SEC_ANT][7] = (md.feat.sync_score_ant[2] <= -0.7 && md.feat.sync_score_ant[2]>= -1) ? 1 : (1 - (md.feat.sync_score_ant[2] + .7));
    //print score
    cout<<"WILD 10a: "<<md.conds_passed[SEC_ANT][4]*5<<"; "<< md.feat.comp_score_ant_mespa<<endl;
    cout<<"WILD 10b: "<<md.conds_passed[SEC_ANT][5]*5<<"; "<<md.feat.comp_score_ant_mespb<<endl;
    cout<<"WILD 10c: "<<md.conds_passed[SEC_ANT][6]*5<<"; "<<md.feat.sync_score_ant[1]<<endl;
    cout<<"WILD 10d: "<<md.conds_passed[SEC_ANT][7]*5<<"; "<<md.feat.sync_score_ant[2]<<endl;
    
    //print total socre for this mutant
    cout<<"WILD ANT SUM: "<<(md.conds_passed[SEC_ANT][0] * md.cond_scores[SEC_ANT][0]) +
    (md.conds_passed[SEC_ANT][1] * md.cond_scores[SEC_ANT][1]) +
    (md.conds_passed[SEC_ANT][4] * md.cond_scores[SEC_ANT][4]) +
    (md.conds_passed[SEC_ANT][5] * md.cond_scores[SEC_ANT][5]) +
    (md.conds_passed[SEC_ANT][6] * md.cond_scores[SEC_ANT][6]) +
    (md.conds_passed[SEC_ANT][7] * md.cond_scores[SEC_ANT][7])<<endl;
    
    return
    (md.conds_passed[SEC_ANT][0] * md.cond_scores[SEC_ANT][0]) +
    (md.conds_passed[SEC_ANT][1] * md.cond_scores[SEC_ANT][1]) +
    (md.conds_passed[SEC_ANT][4] * md.cond_scores[SEC_ANT][4]) +
    (md.conds_passed[SEC_ANT][5] * md.cond_scores[SEC_ANT][5]) +
    (md.conds_passed[SEC_ANT][6] * md.cond_scores[SEC_ANT][6]) +
    (md.conds_passed[SEC_ANT][7] * md.cond_scores[SEC_ANT][7]);
}


double test_delta_mutant_post (mutant_data& md, features& wtfeat) {
    //delta post
    //continuous score calculation
    double temp=0;
    if (1.07 < (md.feat.period_post / wtfeat.period_post) && (md.feat.period_post / wtfeat.period_post) < 1.20){
        temp=1;
    }
    else if (1.07 > (md.feat.period_post / wtfeat.period_post)){
        temp= (md.feat.period_post / wtfeat.period_post) / 1.07;
    }
    else if ((md.feat.period_post / wtfeat.period_post)> 1.20){
        temp= 2-(md.feat.period_post / wtfeat.period_post)/1.20;
    }
    md.conds_passed[SEC_POST][0]=temp;
    //print score
    cout<<"DELTA 0: "<<md.conds_passed[SEC_POST][0]*5<<"; "<<"IMH1 period: "<<md.feat.period_post<< " "<< wtfeat.period_post<< "  "<<md.feat.period_post / wtfeat.period_post <<endl;
    
    //print total socre for this mutant
    cout<<"DELTA POST SUM "<<(md.conds_passed[SEC_POST][0] * md.cond_scores[SEC_POST][0])<<endl;
    return (md.conds_passed[SEC_POST][0] * md.cond_scores[SEC_POST][0]);
    
}

double test_delta_mutant_ant (mutant_data& md, features& wtfeat) {
    
    //delta 1
    md.conds_passed[SEC_ANT][0] = md.feat.sync_score_ant[IMH1] < 0.7;
    //print score
    cout<<"DELTA 1: "<<md.conds_passed[SEC_ANT][0]*5<<"; "<< md.feat.sync_score_ant[IMH1]<<endl;
    
    
    
    //delta 2
    //calculate continuous score
    double temp=0;
    double ratio =(md.feat.amplitude_ant_time[IMH1][0] / wtfeat.amplitude_ant_time[IMH1][0]);
    if (ratio< 0.85 && ratio > 0.3){
        temp=1;
    }
    else if (ratio > .85){
        temp= (2-ratio/.85);
    }
    md.conds_passed[SEC_ANT][1]=temp;
    //print score
    cout<<"DELTA 2: "<<md.conds_passed[SEC_ANT][1]*5<<"; "<<md.feat.amplitude_ant_time[IMH1][0]<< " " <<wtfeat.amplitude_ant_time[IMH1][0] <<" "<<md.feat.amplitude_ant_time[IMH1][0] / wtfeat.amplitude_ant_time[IMH1][0] <<endl;
    
    //  deltac.3.
    //NOTE: using amplitude_ant_time[delta][0] to save space
    if(md.feat.amplitude_ant_time[IMDELTA][0]> 100000){md.feat.amplitude_ant_time[IMDELTA][0]=0;}
    md.conds_passed[SEC_ANT][2] = md.feat.amplitude_ant_time[IMDELTA][0] / wtfeat.amplitude_ant_time[IMDELTA][0] < AMP_SAT;
    //print score
    cout<<"DELTA 3: "<<md.conds_passed[SEC_ANT][2]*5<<"; mespa amp: "<< md.feat.amplitude_ant_time[IMDELTA][0]<<"; mespa amp wt: "<< wtfeat.amplitude_ant_time[IMDELTA][0]<<"; mespa rastio: "<<md.feat.amplitude_ant_time[IMDELTA][0] / wtfeat.amplitude_ant_time[IMDELTA][0]<<endl;
    
    
    //delta 4
    md.conds_passed[SEC_ANT][3]= md.feat.sync_score_ant[IMMESPB] <= 0.7 ? 1 : (1- (md.feat.sync_score_ant[IMMESPB]-.7));
    //print score
    cout<<"DELTA 4: "<<md.conds_passed[SEC_ANT][3]*5<<"; "<<"mespb sync: "<< md.feat.sync_score_ant[IMMESPB]<<endl;
    
    //print total socre for this mutant
    cout<<"DELTA ANT SUM "<<(md.conds_passed[SEC_ANT][0] * md.cond_scores[SEC_ANT][0]) +
    (md.conds_passed[SEC_ANT][1] * md.cond_scores[SEC_ANT][1]) +
    (md.conds_passed[SEC_ANT][2] * md.cond_scores[SEC_ANT][2]) +
    (md.conds_passed[SEC_ANT][3] * md.cond_scores[SEC_ANT][3])<<endl;
    return  (md.conds_passed[SEC_ANT][0] * md.cond_scores[SEC_ANT][0]) +
            (md.conds_passed[SEC_ANT][1] * md.cond_scores[SEC_ANT][1]) +
            (md.conds_passed[SEC_ANT][2] * md.cond_scores[SEC_ANT][2]) +
            (md.conds_passed[SEC_ANT][3] * md.cond_scores[SEC_ANT][3]);
}

             
double test_DAPT_mutant_ant (mutant_data& md, features& wtfeat) {
    
    //dapt 1
    md.conds_passed[SEC_ANT][0] = md.feat.sync_score_ant[IMH1] < 0.7;
    //print score
    cout<<"DAPT 1: " <<md.conds_passed[SEC_ANT][0]*5<<"; "<<md.feat.sync_score_ant[IMH1]<<endl;
    
    //dapt 2
    //continuous score calculation
    double temp=0;
    double ratio =(md.feat.amplitude_ant_time[IMH1][2] /  wtfeat.amplitude_ant_time[IMH1][2]);
    if (ratio< 0.85 && ratio > 0.3){
        temp=1;
    }
    else if (ratio > .85){
        temp= (2-ratio/.85);
    }
    md.conds_passed[SEC_ANT][1]=temp;
    //print score
    cout<<"DAPT 2: " <<md.conds_passed[SEC_ANT][1]*5<<"; "<<md.feat.amplitude_ant_time[IMH1][2]<<" "<< wtfeat.amplitude_ant_time[IMH1][2]<<" "<<md.feat.amplitude_ant_time[IMH1][2] / wtfeat.amplitude_ant_time[IMH1][2]<<endl;

    //dapt 3
    md.conds_passed[SEC_ANT][2]= (md.feat.amplitude_ant_time[IMMESPA][2] / wtfeat.amplitude_ant_time[IMMESPA][2]) <= AMP_SAT;
    //print score
    cout<<"DAPT 3: " <<md.conds_passed[SEC_ANT][2]*5<<"; "<<md.feat.amplitude_ant_time[IMMESPA][2]<<" "<< wtfeat.amplitude_ant_time[IMMESPA][2]<<" "<<md.feat.amplitude_ant_time[IMMESPA][2] / wtfeat.amplitude_ant_time[IMMESPA][2]<<endl;

    //depa 4
    md.conds_passed[SEC_ANT][3]= md.feat.sync_score_ant[IMMESPB] <= .7 ? 1 : (1- (md.feat.sync_score_ant[IMMESPB]-.7));
    //print score
    cout<<"DAPT 4: "<<  md.conds_passed[SEC_ANT][3]*5<<"; "<<md.feat.sync_score_ant[IMMESPB]<<endl;
    
    //print total socre for this mutant
    cout<<"DAPT SUM "<<(md.conds_passed[SEC_ANT][0] * md.cond_scores[SEC_ANT][0]) +
    (md.conds_passed[SEC_ANT][1] * md.cond_scores[SEC_ANT][1]) +
    (md.conds_passed[SEC_ANT][2] * md.cond_scores[SEC_ANT][2]) +
    (md.conds_passed[SEC_ANT][3] * md.cond_scores[SEC_ANT][3])<<endl;
    
    return  (md.conds_passed[SEC_ANT][0] * md.cond_scores[SEC_ANT][0]) +
            (md.conds_passed[SEC_ANT][1] * md.cond_scores[SEC_ANT][1]) +
            (md.conds_passed[SEC_ANT][2] * md.cond_scores[SEC_ANT][2]) +
            (md.conds_passed[SEC_ANT][3] * md.cond_scores[SEC_ANT][3]) ;
}

double test_her1over_mutant_ant (mutant_data& md, features& wtfeat) {
    
    //her1over 1
    md.conds_passed[SEC_ANT][0]= (md.feat.amplitude_ant_time[IMH1][1] / wtfeat.amplitude_ant_time[IMH1][1]) <= AMP_SAT ? 1 : (1- ((md.feat.amplitude_ant_time[IMH1][1] / wtfeat.amplitude_ant_time[IMH1][1])-AMP_SAT));
    //print score
    cout<<"1OVER 1: "<<md.conds_passed[SEC_ANT][0]*5<<"; "<< md.feat.amplitude_ant_time[IMH1][1]<<", "<<wtfeat.amplitude_ant_time[IMH1][1]<<" "<<md.feat.amplitude_ant_time[IMH1][1] / wtfeat.amplitude_ant_time[IMH1][1]<<endl;
    
    //her1over 2
    md.conds_passed[SEC_ANT][1]= (md.feat.amplitude_ant_time[IMDELTA][1] / wtfeat.amplitude_ant_time[IMDELTA][1]) <= AMP_SAT ? 1 : (1- ((md.feat.amplitude_ant_time[IMDELTA][1] / wtfeat.amplitude_ant_time[IMDELTA][1])-AMP_SAT));
    //print score
    cout<<"1OVER 2: "<<md.conds_passed[SEC_ANT][1]*5<<"; "<< md.feat.amplitude_ant_time[IMDELTA][1]<<", "<<wtfeat.amplitude_ant_time[IMDELTA][1]<<" "<<md.feat.amplitude_ant_time[IMDELTA][1] / wtfeat.amplitude_ant_time[IMDELTA][1]<<endl;
    
    //her1over 3
    md.conds_passed[SEC_ANT][2]= (md.feat.amplitude_ant_time[IMMESPA][1] / wtfeat.amplitude_ant_time[IMMESPA][1]) <= AMP_SAT ? 1 : (1- ((md.feat.amplitude_ant_time[IMMESPA][1] / wtfeat.amplitude_ant_time[IMMESPA][1])-AMP_SAT));
    //print score
    cout<<"1OVER 3: "<<md.conds_passed[SEC_ANT][2]*5<<"; "<< md.feat.amplitude_ant_time[IMMESPA][1]<<", "<<wtfeat.amplitude_ant_time[IMMESPA][1]<<" "<<md.feat.amplitude_ant_time[IMMESPA][1] / wtfeat.amplitude_ant_time[IMMESPA][1]<<endl;
    
    //her1over 4
    md.conds_passed[SEC_ANT][3]= (md.feat.sync_score_ant[IMMESPB]) <= 0.5 ? 1 : (1- (md.feat.sync_score_ant[IMMESPB]-.5));
    //print score
    cout<<"1OVER 4: "<<md.conds_passed[SEC_ANT][3]*5<<"; "<<md.feat.sync_score_ant[IMMESPB]<<endl;
    
    //print total socre for this mutant
    cout<<"HER1 OVER SUM "<<(md.conds_passed[SEC_ANT][0] * md.cond_scores[SEC_ANT][0]) +
    (md.conds_passed[SEC_ANT][1] * md.cond_scores[SEC_ANT][1]) +
    (md.conds_passed[SEC_ANT][2] * md.cond_scores[SEC_ANT][2]) +
    (md.conds_passed[SEC_ANT][3] * md.cond_scores[SEC_ANT][3])<<endl;
	
    return  (md.conds_passed[SEC_ANT][0] * md.cond_scores[SEC_ANT][0]) +
            (md.conds_passed[SEC_ANT][1] * md.cond_scores[SEC_ANT][1]) +
            (md.conds_passed[SEC_ANT][2] * md.cond_scores[SEC_ANT][2]) +
            (md.conds_passed[SEC_ANT][3] * md.cond_scores[SEC_ANT][3]);
}

double test_MESPAOVER_mutant_ant (mutant_data& md, features& wtfeat) {
    
    // mespa over 1
    md.conds_passed[SEC_ANT][0] = (md.feat.amplitude_ant_time[IMMESPB][0] / wtfeat.amplitude_ant_time[IMMESPB][0]) <= AMP_SAT ? 1 : (1- ((md.feat.amplitude_ant_time[IMMESPB][0] / wtfeat.amplitude_ant_time[IMMESPB][0])-AMP_SAT));
    //print score
    cout<<"MESPA: "<<md.conds_passed[SEC_ANT][0]*5<<"; "<<md.feat.amplitude_ant_time[IMMESPB][0] << " "<< wtfeat.amplitude_ant_time[IMMESPB][0]<<" "<< md.feat.amplitude_ant_time[IMMESPB][0] / wtfeat.amplitude_ant_time[IMMESPB][0]<<endl;
    double temp = isnan(md.conds_passed[SEC_ANT][0] * md.cond_scores[SEC_ANT][0])? 0: (md.conds_passed[SEC_ANT][0] * md.cond_scores[SEC_ANT][0]);
    
    //print total socre for this mutant
    cout<<"MESPA SUM "<<temp<<endl;
    return isnan(md.conds_passed[SEC_ANT][0] * md.cond_scores[SEC_ANT][0])? 0: (md.conds_passed[SEC_ANT][0] * md.cond_scores[SEC_ANT][0]);
}

double test_MESPBOVER_mutant_ant (mutant_data& md, features& wtfeat) {

    //mespb over 1
    md.conds_passed[SEC_ANT][0] = (md.feat.amplitude_ant_time[IMMESPB][0] / wtfeat.amplitude_ant_time[IMMESPB][0]) <= AMP_SAT ? 1 : (1- ((md.feat.amplitude_ant_time[IMMESPB][0] / wtfeat.amplitude_ant_time[IMMESPB][0])-AMP_SAT));
    //print score
    cout<<"MESPB: "<<md.conds_passed[SEC_ANT][0]*5<<"; "<<md.feat.amplitude_ant_time[IMMESPB][0] << " "<< wtfeat.amplitude_ant_time[IMMESPB][0]<<" "<< md.feat.amplitude_ant_time[IMMESPB][0] / wtfeat.amplitude_ant_time[IMMESPB][0]<<endl;
    
    //print total socre for this mutant
    double temp = isnan((md.conds_passed[SEC_ANT][0] * md.cond_scores[SEC_ANT][0])) ? 0 : (md.conds_passed[SEC_ANT][0] * md.cond_scores[SEC_ANT][0]);
    cout<<"MEPSB SUM"<<temp<<endl;
    return isnan((md.conds_passed[SEC_ANT][0] * md.cond_scores[SEC_ANT][0])) ? 0 : (md.conds_passed[SEC_ANT][0] * md.cond_scores[SEC_ANT][0]);
}

double test_her1over_mutant_post (mutant_data& md, features& wtfeat) {
    return 0; //no tests
}

double test_DAPT_mutant_post (mutant_data& md, features& wtfeat) {
    return 0; //no tests
}

double test_MESPAOVER_mutant_post (mutant_data& md, features& wtfeat) {
    return 0; //no tests
}

double test_MESPBOVER_mutant_post (mutant_data& md, features& wtfeat) {
    return 0; //no tests
}

