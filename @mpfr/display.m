function display(c)
%DISPLAY   Implements screen display for mpfr
%

% written  07.11.2011     T.Xu

rnd = mx_mpfr_getround(getround());
c_str = mx_display(c,rnd);

if numel(c_str)==1
    if c_str.mantissa(1) == '-'
        disp([inputname(1),' = -0.',c_str.mantissa(2:end),' E',num2str(c_str.exp)])    
    else
        disp([inputname(1),' = 0.',c_str.mantissa,' E',num2str(c_str.exp)])
    end
else
    s=size(c_str);
    if length(s)==2 % 2-dim array
        for j=1:s(2)
            for i=1:s(1)
                if c_str(i,j).mantissa(1) == '-'
                    disp([inputname(1),'(',num2str(i),',',num2str(j),') = -0.',c_str(i,j).mantissa(2:end),' E',num2str(c_str(i,j).exp)])
                else
                    disp([inputname(1),'(',num2str(i),',',num2str(j),') = 0.',c_str(i,j).mantissa,' E',num2str(c_str(i,j).exp)])
                end
            end
        end
    else
        dims = length(s);
        subs{dims} = 0;
        idx = zeros(1,dims);
        multidim(subs,idx,dims,s,c_str,inputname(1));
    end
end

function multidim(subs,idx,k,s,c_str,vname)
if k==0
    SU.type ='()';
    SU.subs = subs;
    x = subsref(c_str,SU);
    idx_str = num2str(idx(1));
    for j=2:length(idx)
        idx_str = [idx_str,',',num2str(idx(j))];
    end
    if x.mantissa(1) == '-'
        disp([vname,'(',idx_str,') = -0.',x.mantissa(2:end),' E',num2str(x.exp)])
    else    
        disp([vname,'(',idx_str,') = 0.',x.mantissa,' E',num2str(x.exp)])
    end
else
    for i=1:s(k)
        subs{k} = i;
        idx(k) = i;
        multidim(subs,idx,k-1,s,c_str,vname);
    end
end