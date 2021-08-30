function Score = IGD(PopObj,PF,no_objectives)
% <metric> <min>
% Inverted generational distance

%--------------------------------------------------------------------------
% Copyright (c) 2016-2017 BIMK Group. You are free to use the PlatEMO for
% research purposes. All publications which use this platform or any code
% in the platform should acknowledge the use of "PlatEMO" and reference "Ye
% Tian, Ran Cheng, Xingyi Zhang, and Yaochu Jin, PlatEMO: A MATLAB Platform
% for Evolutionary Multi-Objective Optimization [Educational Forum], IEEE
% Computational Intelligence Magazine, 2017, 12(4): 73-87".
%--------------------------------------------------------------------------

     %Distance = min(pdist2(NPF,NPopObj),[],2);   %min(pdist2(PF,PopObj),[],2);
     Distance = min(pdist2(PF,PopObj),[],2);
     Score    = mean(Distance);


% % % % % %normalization
% % % %      for i=1:no_objectives
% % % %         % PopObj(:,i) = (PopObj(:,i)-min(PopObj(:,i)))./(max(PopObj(:,i))-min(PopObj(:,i)));
% % % %          NPopObj(:,i) = (PopObj(:,i)-min(PF(:,i)))./(max(PF(:,i))-min(PF(:,i)));
% % % %          NPF(:,i) = (PF(:,i)-min(PF(:,i)))./(max(PF(:,i))-min(PF(:,i)));
% % % %          
% % % %      end
% % % %     % NPopObj
% % % %     % NPF
% % % % %      size(NPopObj)
% % % % %      size(NPF)
% % % % 
% % % % %      Distance = min(pdist2(NPF,NPopObj),[],2);   %min(pdist2(PF,PopObj),[],2);
% % % % %      Distance    = mean(Distance);
% % % %     Summ = 0;
% % % %   
% % % % 	   for i=1: size(NPF,1)
% % % %             tempdis = distanceToClosedPoint(NPF(i,:), NPopObj);
% % % % 			Summ = Summ + tempdis*tempdis; %Math.pow(distanceToClosedPoint(NPF(i,:), NPopObj), pow_);
% % % %        end
% % % %        %Summ
% % % % 		%// STEP 4. Obtain the sqrt of the sum
% % % % 		Summ = sqrt(Summ); % Math.pow(sum, 1.0 / pow_);
% % % %         
% % % % 		%// STEP 5. Divide the sum by the maximum number of points of the front
% % % % 		Score  = Summ / size(NPF,1);
% % % % 
% % % % 		%return generationalDistance;
% % % % end
% % % % 
% % % % function edistance = distance( a,  b) 
% % % % %a
% % % % %b
% % % % 
% % % % 		 edistance = 0.0;
% % % % 
% % % %         for i = 1:length(a)
% % % % 			edistance = edistance +((a(i) - b(i))^2)  ;
% % % %         end
% % % % 		edistance = sqrt(edistance);
% % % % 	
% % % % end
% % % % 
% % % % % 	/**
% % % % % 	 * Gets the distance between a point and the nearest one in a given front
% % % % % 	 * (the front is given as <code>double [][]</code>)
% % % % % 	 * 
% % % % % 	 * @param point
% % % % % 	 *            The point
% % % % % 	 * @param front
% % % % % 	 *            The front that contains the other points to calculate the
% % % % % 	 *            distances
% % % % % 	 * @return The minimun distance between the point and the front
% % % % % 	 **/
% % % % function  mindis =  distanceToClosedPoint(point, front) 
% % % % 		 minDistance = distance(point, front(1,:));
% % % % 
% % % % 		for i = 2:size(front,1) 
% % % %                  aux = distance(point, front(i,:));
% % % %                 if (aux < minDistance) 
% % % %                     minDistance = aux;
% % % %                 end
% % % %         end
% % % % 
% % % % 		 mindis = minDistance;
% % % % end